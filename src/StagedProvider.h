#pragma once

#include <assert.h>
#include <limits.h>
#include <iostream>

#include "Record.h"
#include "Provider.h"
#include "IODevice.h"

using namespace std;

/**
 * A configuration class that sets values for the Staged Provider class
 */
class StagingConfig {
public:
    StagingConfig() {}                        // class constructor to initialize class

    uint64_t recordCount;                     // how many records were stored in the run that we are staging

    uint64_t storageStartOffset;              // the location (offset) on the storage device where the first records is stored
    uint64_t stagingStartOffset;              // the location on the staging device where we will temporarily store the block
    uint64_t stagingLength;                   // the amount of storage that is reserve on the staging device to stage the block (256K-16K)

    uint8_t *buffer;                          // the buffer where we can store the next records to return (part of our 100MB)
    int bufferLength;                         // the amount of space in the buffer that we can use to stage data

    uint8_t *transferBuffer;                  // the buffer that we temporarily use to read a block from HDD and write back to SSD
    uint64_t transferLength;                  // the length of the transfer buffer (should equal stagingLength+bufferLength)
    
    shared_ptr<IODevice> storage = nullptr;   // the IoDevice where the records are stored (probably an HDD)
    shared_ptr<IODevice> staging = nullptr;   // the IoDevice where we will stage one block of data from storage (probably an SSD)
};

/**
 * This class is utilized to transfer records between the SSD and HDD
 */
class StagedProvider: public Provider {
public:
    /**
      * Class constructor that takes in Staging Config
      * @param cfg staging config
     */
    StagedProvider(unique_ptr<StagingConfig> &cfg);
    /**
     * Gets the next record from from the (staging) chunk of HDD
     * Places the next HDD chunk into SDD for reading
     * @returns a pointer to the next record or a null pointer if a next record doesn't exist
     */
    shared_ptr<Record> next() override;

private:
    unique_ptr<StagingConfig> cfg; // the staging config class that guides retrieval of data from HDD to SDD

    uint64_t storageOffset;        // the current location (offset) on the storage device to be read from
    uint64_t storageRemaining;     // the number of bytes left in storage to retrieve records from

    uint64_t stagingOffset;        // the current location (offset) on the staging device to be read from
    uint64_t stagingRemaining;     // the number of bytes left in the staging device to retrieve records from

    int bufferOffset;              // the current location within the buffer to return records from
    int bufferRemaining;           // the number of bytes within the buffer that are left

    uint64_t totalRecordsReturned; // total number of records returned by next() at the current point in time
};
