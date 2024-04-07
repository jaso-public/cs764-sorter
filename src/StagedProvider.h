#pragma once

#include <assert.h>
#include <limits.h>
#include <iostream>

#include "Record.h"
#include "Provider.h"
#include "IODevice.h"

using namespace std;


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


class StagingConfig {
public:
    StagingConfig() {}

    uint64_t recordCount;

    uint64_t storageStartOffset;
    uint64_t stagingStartOffset;
    uint64_t stagingLength;

    uint8_t *buffer;
    int bufferLength;

    uint8_t *transferBuffer;
    uint64_t transferLength;
    
    shared_ptr<IODevice> storage = nullptr;
    shared_ptr<IODevice> staging = nullptr;
};

class StagedProvider: public Provider {
public:
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
