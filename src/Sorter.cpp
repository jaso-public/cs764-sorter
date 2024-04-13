#include <iostream>
#include <iomanip>

#include "Sorter.h"

#include "StorageProvider.h"
#include "StagedProvider.h"
#include "TournamentPQ.h"


void SorterConfig::writeStats(std::ostream& out) {
    out << "Sorter Configuration:" << endl;
    out << "    spill fraction   : " << fixed << setprecision(3) << (fraction*100.0)  << "%" << endl;
    out << "    cache size       : " << memoryBlockSize << endl;
    out << "    memory size      : " << (memoryBlockSize * memoryBlockCount) << endl;
    out << "    HDD read size    : " << hddReadSize << endl;
    out << "    SSD read size    : " << ssdReadSize << endl;
    out << "    SSD size         : " << ssdStorageSize << endl;
}

Sorter::Sorter(unique_ptr<SorterConfig> &config, shared_ptr<Provider> src) {
    startTime = std::chrono::high_resolution_clock::now();

    cfg = std::move(config);

    if(cfg->ssdDevice == nullptr) {
        cerr << "we need an ssd device." << endl;
        exit(1);
    }

    if(cfg->hddDevice == nullptr) {
        cerr << "we need an hdd device." << endl;
        exit(1);
    }

    source = src;

    ssdOffset = 0;
    hddOffset = 0;

    ssdRemaining = cfg->ssdStorageSize;

    bufferLength = cfg->memoryBlockSize * cfg->memoryBlockCount;
    buffer = new uint8_t[bufferLength];
    lastMemoryRun= bufferLength;

    sortedProvider = startSort();
}

shared_ptr<Record> Sorter::next() {
    return sortedProvider->next();
}


shared_ptr<Provider> Sorter::startSort() {
    int maxRecordsPerRun = cfg->memoryBlockSize / Record::getRecordSize();

    vector<shared_ptr<Provider>> singles(maxRecordsPerRun);
    for (int i = 0; i < maxRecordsPerRun; ++i) {
        singles[i] = make_unique<SingleProvider>();
    }

    bool endReached = false;
    while (!endReached) {
        int recordCount = 0;
        while (recordCount < maxRecordsPerRun) {
            shared_ptr<Record> recordPtr = source->next();
            if (!recordPtr) {
                endReached = true;
                break;
            }
            shared_ptr<SingleProvider> singleProvider = dynamic_pointer_cast<SingleProvider>(singles[recordCount++]);
            singleProvider->reset(recordPtr);
        }

        if (recordCount > 0) {
            // find the buffer that we are going to fill.
            if (lastMemoryRun == cfg->memoryBlockSize) makeFreeSpace();

            lastMemoryRun -= cfg->memoryBlockSize;

            shared_ptr<Provider> pq = make_shared<TournamentPQ>(singles, recordCount);
            for (int i = 0; i < recordCount; i++) {
                shared_ptr<Record> ptr = pq->next();
                int storeOffset = lastMemoryRun + i * Record::getRecordSize();
                ptr->store(buffer + storeOffset);
            }
            memoryRuns.push_back(make_shared<Run>(recordCount, lastMemoryRun));
        }
    }
    // if there was nothing to sort then return an empty provider.
    if (memoryRuns.size() + ssdRuns.size() + hddRuns.size() == 0) {
        shared_ptr<Provider> result = make_shared<EmptyProvider>();
        return result;
    }

    // see if we can do the final merge with the memory we have.
    // i.e not too many runs and no need to stage hdd runs to ssd
    int memoryRequired = ssdRuns.size() * cfg->ssdReadSize + (hddRuns.size() + 1) * cfg->hddReadSize;
    if (memoryRequired < cfg->memoryBlockCount * cfg->memoryBlockSize) {
        if (memoryRequired > lastMemoryRun) {
            int toRelease = (memoryRequired - lastMemoryRun + cfg->memoryBlockSize - 1) / cfg->memoryBlockSize;
            releaseMemory(toRelease);
        }
        vector<shared_ptr<Provider>> providers(memoryRuns.size() + ssdRuns.size() + hddRuns.size());
        int index = 0;
        for (shared_ptr<Run> run: memoryRuns) {
            shared_ptr<Provider> memPtr = make_shared<MemoryProvider>(buffer+run->offset, run->numRecords);
            providers[index++] = memPtr;
        }

        // start using the memory from the beginning of the buffer to stage data from the ssd/hdd.
        int offset = 0;

        for (shared_ptr<Run> run: hddRuns) {
            unique_ptr<StorageConfig> storageConfig = make_unique<StorageConfig>();
            storageConfig->recordCount = run->numRecords;
            storageConfig->startOffset = run->offset;
            storageConfig->buffer = buffer;
            storageConfig->bufferLength = cfg->hddReadSize;
            storageConfig->storage = cfg->hddDevice;
            offset += cfg->hddReadSize;
            providers[index++] = make_shared<StorageProvider>(storageConfig);
        }

        for (shared_ptr<Run> run: ssdRuns) {
            unique_ptr<StorageConfig> storageConfig = make_unique<StorageConfig>();
            storageConfig->recordCount = run->numRecords;
            storageConfig->startOffset = run->offset;
            storageConfig->buffer = buffer;
            storageConfig->bufferLength = cfg->ssdReadSize;
            storageConfig->storage = cfg->ssdDevice;
            offset += cfg->ssdReadSize;
            providers[index++] = make_shared<StorageProvider>(storageConfig);
        }

        shared_ptr<Provider> result = make_shared<TournamentPQ>(providers, index);
        return result;
    }

      // we did not have enough memory to do the final merge, so lets flush all of our memory
      // runs and use all the memory to stage the final merge run.
    releaseMemory(memoryRuns.size());


    // there are two constraints that we have to worry about now:
    // 1. do we have enough free space on the ssd to do the staging?
    // 2. do we have too many runs to merge in the final pass?


    // max number of merge runs that can be merged using cfg.ssdReadSize chunk sized memory for each run
    // Note we reserve one cfg.hddReadSize block of memory to transfer data from the hdd back to the ssd
    int maxMergeRuns = ((cfg->memoryBlockCount * cfg->memoryBlockSize) - cfg->hddReadSize) / cfg->ssdReadSize;
    int runsToMergeForCount = ssdRuns.size() + hddRuns.size() - maxMergeRuns;

    // figure out how much space we need for staging hdd data
    long stagingRequired = (hddRuns.size() + 1) * (cfg->hddReadSize - cfg->ssdReadSize);
    int runsToMergeForSpace = 0;
    for (shared_ptr<Run> run: ssdRuns) {
        if (run->offset > stagingRequired) break;
        runsToMergeForSpace++;
    }

    int runsToMerge = max(runsToMergeForSpace, runsToMergeForCount);

    cout << "------------------" << "\n";
    cout << "memoryRuns.size():" << memoryRuns.size() << "\n";
    cout << "ssdRuns.size():" << ssdRuns.size() << "\n";
    cout << "hddRuns.size():" << hddRuns.size() << "\n";
    cout << "runsToMerge:" << runsToMerge << "\n";

    vector<shared_ptr<Provider>> providers(runsToMerge);

    long recordCount = 0;
    for (int i = 0; i < runsToMerge; i++) {
        shared_ptr<Run> run = ssdRuns[0];
        ssdRuns.erase(ssdRuns.begin());
        recordCount += run->numRecords;
        int offset = cfg->memoryBlockSize + i * cfg->ssdReadSize;

        unique_ptr<StorageConfig> storageConfig = make_unique<StorageConfig>();
        storageConfig->recordCount = run->numRecords;
        storageConfig->startOffset = run->offset;
        storageConfig->buffer = buffer;
        storageConfig->bufferLength = cfg->ssdReadSize;
        storageConfig->storage = cfg->ssdDevice;
        providers[i] = make_shared<StorageProvider>(storageConfig);
    }

    storeRun(make_shared<TournamentPQ>(providers, runsToMerge), recordCount);

    vector<shared_ptr<Provider>> newProvider(ssdRuns.size() + hddRuns.size());
    providers = newProvider;
    int index = 0;
    int memoryOffset = cfg->hddReadSize;


    for (int i = 0; i < hddRuns.size(); i++) {
        shared_ptr<Run> run = hddRuns[i];

        unique_ptr<StagingConfig> stagingCfg = make_unique<StagingConfig>();
        stagingCfg->recordCount = run->numRecords;
        stagingCfg->storage = cfg->hddDevice;
        stagingCfg->storageStartOffset = run->offset;
        stagingCfg->staging = cfg->ssdDevice;
        stagingCfg->stagingStartOffset = i * (cfg->hddReadSize - cfg->ssdReadSize);
        stagingCfg->stagingLength = cfg->hddReadSize - cfg->ssdReadSize;
        stagingCfg->buffer = buffer + memoryOffset;
        stagingCfg->bufferLength = cfg->ssdReadSize;
        stagingCfg->transferBuffer = buffer; // this is always at the start of the memory buffer
        stagingCfg->transferLength = cfg->hddReadSize;
        providers[index++] = make_shared<StagedProvider>(stagingCfg);
        memoryOffset += cfg->ssdReadSize;
    }

    for (shared_ptr<Run> run: ssdRuns) {
        unique_ptr<StorageConfig> storageConfig = make_unique<StorageConfig>();
        storageConfig->recordCount = run->numRecords;
        storageConfig->startOffset = run->offset;
        storageConfig->buffer = buffer;
        storageConfig->bufferLength = cfg->ssdReadSize;
        storageConfig->storage = cfg->ssdDevice;
        providers[index++] = make_shared<StorageProvider>(storageConfig);
        memoryOffset += cfg->ssdReadSize;
    }

    shared_ptr<Provider> result = make_shared<TournamentPQ>(providers, index);
    return result;
}

void Sorter::makeFreeSpace() {
    long sorted = ssdOffset + hddOffset;
    sorted /= cfg->memoryBlockSize;
    sorted += memoryRuns.size();
    // at this point sorted contains the number of 1MB blocks we have.

    int numToMove = (int)(sorted * cfg->fraction);
    if(numToMove < 1) numToMove = 1;

    releaseMemory(numToMove);
}

void Sorter::releaseMemory(int numberBuffersToRelease) {
    vector<shared_ptr<Provider>> providers(numberBuffersToRelease);

    long recordCount = 0;
    int index = 0;

    while(memoryRuns.size() > 0 && index < numberBuffersToRelease) {
        auto run = memoryRuns.back();
        memoryRuns.pop_back();
        providers[index++] = make_shared<MemoryProvider>(buffer+run->offset, run->numRecords);;
        recordCount += run->numRecords;
    }

    // free up the memory that is being merged
    lastMemoryRun += numberBuffersToRelease * cfg->memoryBlockSize;

    storeRun(make_shared<TournamentPQ>(providers, index), recordCount);
}


void Sorter::storeRun(shared_ptr<Provider> provider, long recordCount) {
    int recordSize = Record::getRecordSize();
    long spaceRequired = recordCount * recordSize;

    shared_ptr<IODevice> device;
    long deviceOffset;

    long ssdRequired = roundUp(spaceRequired, cfg->ssdReadSize);
    if(ssdRequired <= ssdRemaining) {
        device = cfg->ssdDevice;
        deviceOffset = ssdOffset;
        ssdRuns.push_back(make_shared<Run>(recordCount, ssdOffset));
        ssdOffset += ssdRequired;
        ssdRemaining -= ssdRequired;
    }
    else {
        long hddRequired = roundUp(spaceRequired, cfg->hddReadSize);
        device = cfg->hddDevice;
        deviceOffset = hddOffset;
        hddRuns.push_back(make_shared<Run>(recordCount, hddOffset));
        hddOffset += hddRequired;
    }

    int bufferOffset = 0;
    int bufferRemaining = cfg->memoryBlockSize;
    while(true) {
        shared_ptr<Record> rPtr = provider->next();
        if(!rPtr) break;
        if(bufferRemaining < recordSize) {
            rPtr->store(buffer + bufferOffset, 0, bufferRemaining);
            int leftOver = recordSize - bufferRemaining;
            device->write(deviceOffset, buffer, cfg->memoryBlockSize);
            deviceOffset += cfg->memoryBlockSize;
            rPtr->store(buffer, bufferRemaining, leftOver);
            bufferOffset = leftOver;
            bufferRemaining = cfg->memoryBlockSize - leftOver;
        } else {
            rPtr->store(buffer+bufferOffset);
            bufferOffset += recordSize;
            bufferRemaining -= recordSize;
        }
    }

    // finally write out what ever is left in the buffer.
    device->write(deviceOffset, buffer, bufferOffset);
}

long Sorter::roundUp(long value, long multiple) {
    long quotient = value / multiple;
    if(quotient * multiple == value) return value;
    return (quotient + 1) * multiple;
}

void Sorter::writeStats(std::ostream& out) {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - startTime);
    double elapsed = duration.count();
    elapsed = elapsed / 1e9;

    out << "Sorter results: " << endl;
    out << fixed << setprecision(6) << "    compare count    : " << Record::getCompareCount() << " comparisons" << endl;
    out << fixed << setprecision(6) << "    elapsed time     : " << elapsed << " seconds" << endl;
 }


