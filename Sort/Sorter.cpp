#include "Sorter.h"

Sorter::Sorter(SorterConfig cfg, Provider* source) {
    this->cfg = cfg;
    this->source = source;

    this->ssdOffset = 0;
    this->ssdRemaining = 0;
    this->hddOffset = 0;

    ssdRemaining = cfg.ssdStorageSize;

    this->buffer = new uint8_t[cfg.memoryBlockSize * cfg.memoryBlockCount];
    lastMemoryRun = sizeof(buffer);

    this->sortedProvider = startSort();
}

shared_ptr<Record> Sorter::next() {
    return sortedProvider->next();
}


Provider* Sorter::startSort() {
    Record otherClass;
    otherClass.resetCompareCount();

    int maxRecordsPerRun = cfg.memoryBlockSize / cfg.recordSize;

    SingleProvider s(cfg);
    vector<SingleProvider*> singles(maxRecordsPerRun, &s);

    bool endReached = false;
    while (!endReached) {
        int recordCount = 0;
        while (recordCount < maxRecordsPerRun) {
            shared_ptr<Record> recordPtr = source->next();
            if (!recordPtr) {
                endReached = true;
                break;
            }
            singles[recordCount++]->reset(recordPtr);
        }

        if (recordCount > 0) {
            // find the buffer that we are going to fill.
            if (lastMemoryRun == cfg.memoryBlockSize) makeFreeSpace();

            lastMemoryRun -= cfg.memoryBlockSize;

            vector<Provider*> providerFromSingles(singles.begin(), singles.end());
            TournamentPQ pq(providerFromSingles, keyOffset, recordCount);
            for (int i = 0; i < recordCount; i++) {
                shared_ptr<Record> ptr = pq.next();
                Record r = *ptr;
                r.store(buffer, lastMemoryRun + i * cfg.recordSize, 1);
            }
            Run run(recordCount, lastMemoryRun);
            memoryRuns.push_back(run);
        }

    }
    // if there was nothing to sort then return an empty provider.
    if (memoryRuns.size() + ssdRuns.size() + hddRuns.size() == 0) {
        EmptyProvider e;
        Provider* providerPtr = reinterpret_cast<Provider *>(&e);
        return providerPtr;
    }

    // see if we can do the final merge with the memory we have.
    // i.e not too many runs and no need to stage hdd runs to ssd
    int memoryRequired = ssdRuns.size() * cfg.ssdReadSize + (hddRuns.size() + 1) * cfg.hddReadSize;
    if (memoryRequired < cfg.memoryBlockCount * cfg.memoryBlockSize) {
        if (memoryRequired > lastMemoryRun) {
            int toRelease = (memoryRequired - lastMemoryRun + cfg.memoryBlockSize - 1) / cfg.memoryBlockSize;
            releaseMemory(toRelease);
        }

        vector<Provider*> providers(memoryRuns.size() + ssdRuns.size() + hddRuns.size());
        int index = 0;

        for (Run run: memoryRuns) {
            MemoryProvider m(buffer, run.offset, cfg);
            providers[index++] = &m;
        }
        // start using the memory from the beginning of the buffer to stage data from the ssd/hdd.
        int offset = 0;

        for (Run run: hddRuns) {
            StorageProvider s(cfg.hddDevice, run.offset, buffer, offset, cfg.hddReadSize, cfg);
            offset += cfg.hddReadSize;
        }

        for (Run run: ssdRuns) {
            StorageProvider s(cfg.ssdDevice, run.offset, buffer, offset, cfg.ssdReadSize,
                             cfg);
            offset += cfg.ssdReadSize;
        }
        TournamentPQ t(providers, keyOffset, index);
        Provider* providerPointer = &t;
        return providerPointer;
    }

    // we did not have enough memory to do the final merge, so lets flush all of our memory
    // runs and use all the memory to stage the final merge run.
    releaseMemory(memoryRuns.size());


    // there are two constraints that we have to worry about now:
    // 1. do we have enough free space on the ssd to do the staging?
    // 2. do we have too many runs to merge in the final pass?


    // max number of merge runs that can be merged using cfg.ssdReadSize chunk sized memory for each run
    // Note we reserve one cfg.hddReadSize block of memory to transfer data from the hdd back to the ssd
    int maxMergeRuns = ((cfg.memoryBlockCount * cfg.memoryBlockSize) - cfg.hddReadSize) / cfg.ssdReadSize;
    int runsToMergeForCount = ssdRuns.size() + hddRuns.size() - maxMergeRuns;

    // figure out how much space we need for staging hdd data
    long stagingRequired = (hddRuns.size() + 1) * (cfg.hddReadSize - cfg.ssdReadSize);
    int runsToMergeForSpace = 0;
    for (Run run: ssdRuns) {
        if (run.offset > stagingRequired) break;
        runsToMergeForSpace++;
    }

    int runsToMerge = max(runsToMergeForSpace, runsToMergeForCount);

    cout << "------------------" << "\n";
    cout << "memoryRuns.size():" << memoryRuns.size() << "\n";
    cout << "ssdRuns.size():" << ssdRuns.size() << "\n";
    cout << "hddRuns.size():" << hddRuns.size() << "\n";
    cout << "runsToMerge:" << runsToMerge << "\n";

    vector<Provider*> providers(runsToMerge);

    long recordCount = 0;
    for (int i = 0; i < runsToMerge; i++) {
        Run run = ssdRuns[0];
        ssdRuns.erase(ssdRuns.begin());
        recordCount += run.numRecords;
        int offset = cfg.memoryBlockSize + i * cfg.ssdReadSize;
        StorageProvider s(cfg.ssdDevice, run.offset, buffer, offset,
                          cfg.ssdReadSize, cfg);
        providers[i] = &s;
    }


    TournamentPQ tPQ(providers, keyOffset, runsToMerge);
    Provider* provider = &tPQ;
    storeRun(provider, recordCount);


    vector<Provider*> newProvider(ssdRuns.size() + hddRuns.size());
    providers = newProvider;
    int index = 0;
    int memoryOffset = cfg.memoryBlockSize;


    for (int i = 0; i < hddRuns.size(); i++) {
        Run run = hddRuns[i];


        StagingConfig stagingCfg;
        stagingCfg.recordSize = cfg.recordSize;
        stagingCfg.recordCount = run.numRecords;
        stagingCfg.storage = cfg.hddDevice;
        stagingCfg.storageStartOffset = run.offset;
        stagingCfg.staging = cfg.ssdDevice;
        stagingCfg.stagingStartOffset = i * (cfg.hddReadSize - cfg.ssdReadSize);
        stagingCfg.stagingLength = cfg.hddReadSize - cfg.ssdReadSize;
        stagingCfg.buffer = buffer;
        stagingCfg.bufferStartOffset = memoryOffset;
        stagingCfg.bufferLength = cfg.ssdReadSize;
        stagingCfg.transferBuffer = buffer;
        stagingCfg.transferStartOffset = 0;
        stagingCfg.transferLength = cfg.hddReadSize;
        stagingCfg.keySize = cfg.keySize;
        stagingCfg.keyOffset = cfg.keyOffset;
        StagedProvider sp(stagingCfg);
        providers[index++] = &sp;
        memoryOffset += cfg.ssdReadSize;
    }

    for (Run run: ssdRuns) {
        StorageProvider storageProvider(cfg.ssdDevice, run.offset, buffer,
                        memoryOffset, cfg.ssdReadSize, cfg);
        providers[index++] = &storageProvider;
        memoryOffset += cfg.ssdReadSize;
    }

    TournamentPQ t(providers, keyOffset, index);
    Provider* providerPointer = &t;
    return providerPointer;
}

void Sorter::makeFreeSpace() {
    long sorted = ssdOffset + hddOffset;
    sorted /= cfg.memoryBlockSize;
    sorted += memoryRuns.size();
    // at this point sorted contains the number of 1MB blocks we have.

    int numToMove = (int)(sorted * cfg.fraction);
    if(numToMove < 1) numToMove = 1;

    releaseMemory(numToMove);
}

void Sorter::releaseMemory(int numberBuffersToRelease) {
    vector<Provider*> providers(numberBuffersToRelease);

    long recordCount = 0;
    int index = 0;

    while(memoryRuns.size() > 0 && index < numberBuffersToRelease) {

        Run run = memoryRuns[memoryRuns.size()-1];
        SorterConfig runConfig;
        runConfig.recordCount = run.numRecords;
        ssdRuns.pop_back();
        MemoryProvider memProv(buffer, run.offset, runConfig);
        providers[index++] = &memProv;
        recordCount += run.numRecords;
    }

    lastMemoryRun += numberBuffersToRelease * cfg.memoryBlockSize;

    TournamentPQ t(providers, keyOffset, index);
    Provider* provider = &t;
    storeRun(provider, recordCount);
}

void Sorter::storeRun(Provider* provider, long recordCount) {
    long spaceRequired = recordCount * cfg.recordSize;

    IODevice device("../Files/storeRun.tmp");
    long deviceOffset = 0;

    long ssdRequired = roundUp(spaceRequired, cfg.ssdReadSize);
    if(ssdRequired <= ssdRemaining) {
        device = cfg.ssdDevice;
        deviceOffset = ssdOffset;
        Run run(recordCount, ssdOffset);
        ssdRuns.push_back(run);
        ssdOffset += ssdRequired;
        ssdRemaining -= ssdRequired;
    } else {
        long hddRequired = roundUp(spaceRequired, cfg.hddReadSize);
        device = cfg.hddDevice;
        deviceOffset = hddOffset;
        Run run(recordCount, hddOffset);
        hddRuns.push_back(run);
        hddOffset += hddRequired;
    }

    int bufferOffset = 0;
    int bufferRemaining = cfg.memoryBlockSize;
    while(true) {
        shared_ptr<Record> rPtr = provider->next();
        if(!rPtr) break;
        Record r = *rPtr;
        if(bufferRemaining < cfg.recordSize) {
            r.store(buffer, bufferOffset, bufferRemaining);
            int leftOver = cfg.recordSize-bufferRemaining;
            device.write(deviceOffset, buffer, 0, cfg.memoryBlockSize);
            deviceOffset += cfg.memoryBlockSize;
            r.store(buffer, bufferOffset, leftOver);
            bufferOffset = leftOver;
            bufferRemaining = cfg.memoryBlockSize - leftOver;
        } else {
            r.store(buffer, bufferOffset, 1);
            bufferOffset += cfg.recordSize;
            bufferRemaining -= cfg.recordSize;
        }
    }

    // finally write out what ever is left in the buffer.
    device.write(deviceOffset, buffer, 0, bufferOffset);

}

long Sorter::roundUp(long value, long multiple) {
    long quotient = value / multiple;
    if(quotient * multiple == value) return value;
    return (quotient + 1) * multiple;
}

void Sorter::printStats(){
    cout << "SSD usage:" << cfg.ssdDevice.stats() << "\n";
    cout << "HDD usage:" << cfg.hddDevice.stats() << "\n";
    cout << "total number of record comparisons: " <<  record.getCompareCount() << "\n";
}


