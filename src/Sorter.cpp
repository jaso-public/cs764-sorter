#include <iostream>
#include <iomanip>

#include "Sorter.h"

#include "StorageProvider.h"
#include "StagedProvider.h"
#include "TournamentPQ.h"

/**
 * Prints values held by the class to the output stream including: spill fraction, cache size, memory size, HDD read size, SSD read size, and SSD size
 * @param out stream to write statistics to
*/
void SorterConfig::writeStats(std::ostream& out) {
    out << "Sorter Configuration:" << endl;
    out << "    spill fraction   : " << fixed << setprecision(3) << (fraction*100.0)  << "%" << endl;
    out << "    cache size       : " << memoryBlockSize << endl;
    out << "    memory size      : " << (memoryBlockSize * memoryBlockCount) << endl;
    out << "    HDD read size    : " << hddReadSize << endl;
    out << "    SSD read size    : " << ssdReadSize << endl;
    out << "    SSD size         : " << ssdStorageSize << endl;
}

/**
 * Initializes class' values and begins sorting algorithm
 * @param cfg sorter configuration
 * @param source the provider to obtain records from
*/
Sorter::Sorter(unique_ptr<SorterConfig> &config, shared_ptr<Provider> src) {
    startTime = chrono::high_resolution_clock::now();

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

/**
 * Provides the next, sorted record
 * @return a pointer to the next, sorted record or a null pointer if all records have been returned
*/
shared_ptr<Record> Sorter::next() {
    return sortedProvider->next();
}

/**
 * This method preforms the external merge sort logic
 * @return a provider that will return records in sorted order
*/
shared_ptr<Provider> Sorter::startSort() {
    int maxRecordsPerRun = cfg->memoryBlockSize / Record::getRecordSize();

    // creates a single provider for each record in a run
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
            // gives each provider in singles a record to return
            shared_ptr<SingleProvider> singleProvider = dynamic_pointer_cast<SingleProvider>(singles[recordCount++]);
            singleProvider->reset(recordPtr);
        }

        if (recordCount > 0) {
            // find the buffer that we are going to fill.
            // the first memory block of the buffer is used by the storeRun
            // method to stage data before writing to ssd or hdd.
            // lastMemoryRun is the offset of the last memory run stored.
            // so if we have enough free space, then the current memory run
            // will be stored at lastMemoryRun - the size of a memoryRun
            // (which is the size of a cache block)
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
            int memoryToRelease = roundUp(memoryRequired - lastMemoryRun, cfg->memoryBlockSize);
            int runsToRelease = memoryToRelease / cfg->memoryBlockSize;
            releaseMemory(runsToRelease);
        }

        // set up the providers for the final merge run.
        // add all the memory to the provider as well as ssd/hdd runs with the device's preferred io size.
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
            storageConfig->buffer = buffer + offset;
            storageConfig->bufferLength = cfg->hddReadSize;
            storageConfig->storage = cfg->hddDevice;
            offset += cfg->hddReadSize;  // leave room in the buffer to stage hdd data
            providers[index++] = make_shared<StorageProvider>(storageConfig);
        }

        for (shared_ptr<Run> run: ssdRuns) {
            unique_ptr<StorageConfig> storageConfig = make_unique<StorageConfig>();
            storageConfig->recordCount = run->numRecords;
            storageConfig->startOffset = run->offset;
            storageConfig->buffer = buffer + offset;
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
    // and each run requires enough space to read a ssd read sized chunk into memory
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
    cout << "maxMergeRuns:" << maxMergeRuns << endl;
    cout << "memoryRuns.size():" << memoryRuns.size() << "\n";
    cout << "ssdRuns.size():" << ssdRuns.size() << "\n";
    cout << "hddRuns.size():" << hddRuns.size() << "\n";
    cout << "runsToMerge:" << runsToMerge << "\n";
    cout << "runsToMergeForCount:" << runsToMergeForCount << "\n";
    cout << "runsToMergeForSpace:" << runsToMergeForSpace << "\n";
    cout << "maxMergeRuns:" << maxMergeRuns << "\n";


    vector<shared_ptr<Provider>> providers(runsToMerge);

    long recordCount = 0;
    int offset = cfg->memoryBlockSize; // leave the first block of memory to stage data when storing the run
    for (int i = 0; i < runsToMerge; i++) {
        shared_ptr<Run> run = ssdRuns[0];
        ssdRuns.erase(ssdRuns.begin());
        recordCount += run->numRecords;

        unique_ptr<StorageConfig> storageConfig = make_unique<StorageConfig>();
        storageConfig->recordCount = run->numRecords;
        storageConfig->startOffset = run->offset;
        storageConfig->buffer = buffer + offset;
        storageConfig->bufferLength = cfg->ssdReadSize;
        storageConfig->storage = cfg->ssdDevice;
        providers[i] = make_shared<StorageProvider>(storageConfig);

        offset += cfg-> ssdReadSize;  // advance the offset so each provider gets its own space
    }

    storeRun(make_shared<TournamentPQ>(providers, runsToMerge), recordCount);

    providers.clear();
    int memoryOffset = cfg->hddReadSize;
    uint64_t stagingOffset = 0;

    for(shared_ptr<Run> run : hddRuns) {
        unique_ptr<StagingConfig> stagingCfg = make_unique<StagingConfig>();
        stagingCfg->recordCount = run->numRecords;
        stagingCfg->storage = cfg->hddDevice;
        stagingCfg->storageStartOffset = run->offset;
        stagingCfg->staging = cfg->ssdDevice;
        stagingCfg->stagingStartOffset = stagingOffset;
        stagingCfg->stagingLength = cfg->hddReadSize - cfg->ssdReadSize;
        stagingCfg->buffer = buffer + memoryOffset;
        stagingCfg->bufferLength = cfg->ssdReadSize;
        stagingCfg->transferBuffer = buffer; // this is always at the start of the memory buffer
        stagingCfg->transferLength = cfg->hddReadSize;
        providers.push_back(make_shared<StagedProvider>(stagingCfg));

        memoryOffset += cfg->ssdReadSize;
        stagingOffset += (cfg->hddReadSize - cfg->ssdReadSize);
    }

    for(shared_ptr<Run> run : ssdRuns) {
        unique_ptr<StorageConfig> storageConfig = make_unique<StorageConfig>();
        storageConfig->recordCount = run->numRecords;
        storageConfig->startOffset = run->offset;
        storageConfig->buffer = buffer + memoryOffset;
        storageConfig->bufferLength = cfg->ssdReadSize;
        storageConfig->storage = cfg->ssdDevice;
        providers.push_back(make_shared<StorageProvider>(storageConfig));
        memoryOffset += cfg->ssdReadSize;
    }

    shared_ptr<Provider> result = make_shared<TournamentPQ>(providers, providers.size());
    return result;
}

/**
 * This method enables graceful degradation by defining a spill value (fraction) to spill from memory
 */
void Sorter::makeFreeSpace() {
    long sorted = ssdOffset + hddOffset;
    sorted /= cfg->memoryBlockSize;
    sorted += memoryRuns.size();
    // at this point sorted contains the number of 1MB blocks we have.

    int numToMove = (int)(sorted * cfg->fraction);
    if(numToMove < 1) numToMove = 1;
    if(numToMove > cfg->memoryBlockCount - 1) numToMove = cfg->memoryBlockCount - 1;

    releaseMemory(numToMove);
}

/**
 * This method will free up the memory space before or after a merge so more records can be stored; memory is freed by writing runs to the SSD and/or HDD via storeRuns()
 * @param numberBuffersToRelease the number of runs to free from memory
*/
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

    storeRun(make_shared<TournamentPQ>(providers, numberBuffersToRelease), recordCount);
}


/**
 * This method writes records SSD or the HDD depending on the available space in the SSD
 * @param provider the provider to provide records
 * @param recordCount the total number of records that the provider contains
*/
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

/**
 * This method will return the nearest, rounded up value that is a multiple of the given multiple variable
 * @param value the value to potentially round up
 * @param multiple the desired multiple of the value
 * @return the value, if it is a multiple of multiple or the closest multiple of multiple that is greater than the value
 */
long Sorter::roundUp(long value, long multiple) {
    long quotient = value / multiple;
    if(quotient * multiple == value) return value;
    return (quotient + 1) * multiple;
}

/**
 * Prints out the statistics of the sorting algorithm including the elapsed time it took for sorting to complete and how many comparisons occurred
 * @param out the stream to write the statistics to
*/
void Sorter::writeStats(std::ostream& out) {
    auto end = chrono::high_resolution_clock::now();
    auto duration =chrono::duration_cast<std::chrono::nanoseconds>(end - startTime);
    double elapsed = duration.count();
    elapsed = elapsed / 1e9;

    out << "Sorter results: " << endl;
    out << fixed << setprecision(6) << "    compare count    : " << Record::getCompareCount() << " comparisons" << endl;
    out << fixed << setprecision(6) << "    elapsed time     : " << elapsed << " seconds" << endl;
 }


