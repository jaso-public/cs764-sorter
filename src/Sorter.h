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
    int ssdReadSize = 16 * 1024;                     // size of a SSD read (~16,000 KB)
    long ssdStorageSize = 10L * 1024 * 1024 * 1024;  // size of SSD (10GB)

    shared_ptr<IODevice> hddDevice = nullptr;        // IO device to read and write from/to HDD
    int hddReadSize = 256 * 1024;                    // size of an HDD read (256MB)

    /**
     * Prints values held by the class to the output stream including: spill fraction, cache size, memory size, HDD read size, SSD read size, and SSD size
     * @param out stream to write statistics to
     */
    void writeStats(std::ostream& out);
};

/**
 * This class represents a run which is a group of records that can fit into memory
 */
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
     * @param cfg sorter config
     * @param source the provider to obtain unsorted, records from
     * @param _out a pointer to a stream to display sorter statistics to; if it is a null pointer, then no statistics will be displayed
     */
    Sorter(unique_ptr<SorterConfig> &cfg, shared_ptr<Provider> _source, std::ostream* _out);
    Sorter(unique_ptr<SorterConfig> &cfg, shared_ptr<Provider> _source): Sorter(cfg, _source, nullptr) {}

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
    shared_ptr<Provider> source;                                      // the provider that is giving unsorted records to the class
    std::ostream* out;                                                // out stream to print some sorting info

    shared_ptr<Provider> sortedProvider;                              // the provider that is returning sorted records

    vector<shared_ptr<Run>> memoryRuns;                               // the runs that in DRAM
    vector<shared_ptr<Run>> ssdRuns;                                  // runs in SSD
    vector<shared_ptr<Run>> hddRuns;                                  // runs in HDD

    chrono::time_point<std::chrono::high_resolution_clock> startTime; // the time of the start of the sort; starts as soon as class is initialized

    long ssdOffset;                                                   // current location in SSD
    long ssdRemaining;                                                // total amount of unoccupied/unfilled SSD memory
    long hddOffset;                                                   // current location in HDD

    uint8_t *buffer;                                                  // memory buffer to store records in DRAM
    int bufferLength;                                                 // size of buffer
    int lastMemoryRun;                                                // offset of the last memory run stored


    /**
     * This method preforms the external merge sort logic
     * @return a provider that will return records in sorted order
     */
    shared_ptr<Provider> startSort();
    /**
     * This method enables graceful degradation by defining a spill value (fraction) to spill from memory
     */
    void makeFreeSpace();
    /**
     * This method will free up the memory space before or after a merge so more records can be stored; memory is freed by writing runs to the SSD and/or HDD via storeRuns()
     * @param numberBuffersToRelease the number of runs to free from memory
     */
    void releaseMemory(int numberBuffersToRelease);
    /**
     * This method writes records SSD or the HDD depending on the available space in the SSD
     * @param provider the provider to provide records
     * @param recordCount the total number of records that the provider contains
     */
    void storeRun(shared_ptr<Provider> provider, long recordCount);
    /**
     * This method will return the nearest, rounded up value that is a multiple of the given multiple variable
     * @param value the value to potentially round up
     * @param multiple the desired multiple of the value
     * @return the value, if it is a multiple of multiple or the closest multiple of multiple that is greater than the value
    */
    long roundUp(long value, long multiple);
};

