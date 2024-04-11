#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "Record.h"
#include "Provider.h"
#include "IODevice.h"


using namespace std;

class SorterConfig {
public:
    SorterConfig() {}

    float fraction = 0.005F;
    int memoryBlockSize = 1024 * 1024;
    int memoryBlockCount = 100;

    shared_ptr<IODevice> ssdDevice = nullptr;
    int ssdReadSize = 16 * 1024;
    long ssdStorageSize = 10L * 1024 * 1024 * 1024;;

    shared_ptr<IODevice> hddDevice = nullptr;
    int hddReadSize = 256 * 1024;;
};

class Run {
public:
    Run(long numRecords, long offset): numRecords(numRecords), offset(offset) {}
    long numRecords;
    long offset;
};


class Sorter: public Provider {
public:
    Sorter(unique_ptr<SorterConfig> &cfg, shared_ptr<Provider> source);
    shared_ptr<Record> next() override;

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

