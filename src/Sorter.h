#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "Record.h"
#include "Provider.h"
#include "SingleProvider.h"


#include "Run.h"
#include "Providers/EmptyProvider.h"
#include "Providers/MemoryProvider.h"
#include "Providers/StorageProvider.h"
#include "Providers/StagedProvider.h"
#include "TournamentPQ.h"
using namespace std;

class Sorter: public Provider {
public:
    Sorter(shared_ptr<SorterConfig> cfg, shared_ptr<Provider> source);
    shared_ptr<Record> next() override;
    void printStats();

private:
    shared_ptr<SorterConfig> cfg;
    shared_ptr<Provider> source;

    shared_ptr<Provider> sortedProvider;

    vector <Run> memoryRuns;
    vector <Run> ssdRuns;
    vector <Run> hddRuns;

    long ssdOffset;
    long ssdRemaining;
    long hddOffset;

    uint8_t *buffer;
    int bufferLength;
    int lastMemoryRun;


    shared_ptr<Provider> startSort();
    void makeFreeSpace();
    void releaseMemory(int numberBuffersToRelease);
    void storeRun(Provider *provider, long recordCount);
    long roundUp(long value, long multiple);
};

class SorterConfig {
public:
    SorterConfig {}

    float fraction = 0.005F;
    int memoryBlockSize = 1024 * 1024;
    int memoryBlockCount = 100;

    shared_ptr<IODevice> ssdDevice = nullptr;
    int ssdReadSize = 16 * 1024;
    long ssdStorageSize = 10L * 1024 * 1024 * 1024;;

    shared_ptr<IODevice> hddDevice = nullptr;
    int hddReadSize = 256 * 1024;;
};