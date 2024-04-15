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

/**
 * The sorter class contains all of our logic for completing the sort including: graceful degradation, spilling, and merging
 */
class Sorter: public Provider {
public:
    /**
     * Initializes class' values and begins sorting algorithm
     * @param cfg sorter configuration
     * @param source the provider to obtain records from
     */
    Sorter(unique_ptr<SorterConfig> &cfg, shared_ptr<Provider> source);
    /**
     * Provides the next, sorted record
     * @return a pointer to the next, sorted record or a null pointer if all records have been returned
     */
    shared_ptr<Record> next() override;
    /**
     * Prints out the statistics of the sorting algorithm including the elapsed time it took for sorting to complete and how many comparisons occurred
     * @param out the stream to write the statistics to
     */
    void writeStats(std::ostream& out);

private:
    shared_ptr<SorterConfig> cfg;                                     // class' sorter config class
    shared_ptr<Provider> source;                                      // the provider that is giving records to the class

    shared_ptr<Provider> sortedProvider;                              // the provider that is returning sorted records

    vector<shared_ptr<Run>> memoryRuns;
    vector<shared_ptr<Run>> ssdRuns;
    vector<shared_ptr<Run>> hddRuns;

    chrono::time_point<std::chrono::high_resolution_clock> startTime;  // the time of the start of the sort; starts as soon as class is initialized

    long ssdOffset;                                                    // location in SSD to read from
    long ssdRemaining;                                                 // total amount of unoccupied/filled SSD memory
    long hddOffset;                                                    // location in HDD to read from

    uint8_t *buffer;                                                   // memory buffer to store records in DRAM
    int bufferLength;                                                  // size of DRAM
    int lastMemoryRun;


    shared_ptr<Provider> startSort();
    void makeFreeSpace();
    void releaseMemory(int numberBuffersToRelease);
    void storeRun(shared_ptr<Provider> provider, long recordCount);
    long roundUp(long value, long multiple);
};

