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
      * Class constructor that takes in Staging Config class with the valuing values:
      * @param recordSize           the size of the record (all records are the same size)
      * @param recordCount          the number of records that this provider will return.
      * @param storage              the IoDevice where the records are stored (probably an HDD)
      * @param storageStartOffset   the location (offset) on the storage device where the first records is stored
      * @param staging              the IoDevice where we will stage one block of data from storage (probably an SSD)
      * @param stagingStartOffset   the location on the staging device where we will temporarily store the the block
      * @param stagingLength        the amount of storage that is reserve on the staging device to stage the block (256K-16K)
      * @param buffer               the buffer where we can store the next records to return (part of our 100MB)
      * @param bufferLength         the amount of space in the buffer that we can use to stage data
      * @param transferBuffer       the buffer that we temporarily use to read a block from HDD and write back to SSD.
      * @param transferLength       the length of the transfer buffer (should equal stagingLength+bufferLength)
     */
    StagedProvider(unique_ptr<StagingConfig> &cfg);
    shared_ptr<Record> next() override;

private:
    unique_ptr<StagingConfig> cfg;

    uint64_t storageOffset;
    uint64_t storageRemaining;

    uint64_t stagingOffset;
    uint64_t stagingRemaining;

    int bufferOffset;
    int bufferRemaining;

    uint64_t nextRecord;
};
