#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

#include "Record.h"
#include "Provider.h"
#include "IODevice.h"


using namespace std;

/**
 * This class contains values to provide to the Sorter class
 */
class SorterConfig {
public:

    SorterConfig() {}                                // class constructor to initialize values

    float fraction = 0.005F;                         // spill fraction; enables graceful degradation
    int memoryBlockSize = 1024 * 1024;               // size of a memory block (1MB)
    int memoryBlockCount = 100;                      // total blocks of memory (DRAM is 100MB)

    shared_ptr<IODevice> ssdDevice = nullptr;        // IO device to read and write from/to SSD
    int ssdReadSize = 16 * 1024;                     // size of a read (~16,000 KB)
    long ssdStorageSize = 10L * 1024 * 1024 * 1024;  // size of SSD (10GB)

    shared_ptr<IODevice> hddDevice = nullptr;        // IO device to read and write from/to HDD
    int hddReadSize = 256 * 1024;                    // size of an HDD read (256MB)

    /**
     * Prints values held by the class to the output stream including: spill fraction, cache size, memory size, HDD read size, SSD read size, and SSD size
     * @param out stream to write statistics to
     */
    void writeStats(std::ostream& out);
};

class Run {
public:
    Run(long _numRecords, long _offset): numRecords(_numRecords), offset(_offset) {}
    Run(const Run&) = delete;
    Run& operator=(const Run&) = delete;

    long numRecords;
    long offset;
};


class Sorter: public Provider {
public:
    Sorter(unique_ptr<SorterConfig> &cfg, shared_ptr<Provider> source);
    shared_ptr<Record> next() override;
    void writeStats(std::ostream& out);

private:
    shared_ptr<SorterConfig> cfg;
    shared_ptr<Provider> source;

    shared_ptr<Provider> sortedProvider;

    vector<shared_ptr<Run>> memoryRuns;
    vector<shared_ptr<Run>> ssdRuns;
    vector<shared_ptr<Run>> hddRuns;

    chrono::time_point<std::chrono::high_resolution_clock> startTime;

    long ssdOffset;
    long ssdRemaining;
    long hddOffset;

    uint8_t *buffer;
    int bufferLength;
    int lastMemoryRun;


    shared_ptr<Provider> startSort();
    void makeFreeSpace();
    void releaseMemory(int numberBuffersToRelease);
    void storeRun(shared_ptr<Provider> provider, long recordCount);
    long roundUp(long value, long multiple);
};

