#ifndef CS764_SORTER_STAGEDPROVIDER_H
#define CS764_SORTER_STAGEDPROVIDER_H


#include "IODevice.h"
#include "Provider.h"
#include "Config/StagingConfig.h"

class StagedProvider: public Provider {
private:
    long recordCount;
    uint64_t recordSize;
    uint32_t keyOffset;

    IODevice storage;
    long storageStartOffset;

    IODevice staging;
    long stagingStartOffset;
    long stagingLength;

    char * buffer;
    int bufferStartOffset;
    int bufferLength;

    char * transferBuffer;
    int transferStartOffset;

    long storageOffset = 0;
    long storageRemaining = 0;

    long stagingOffset = 0;
    long stagingRemaining;

    int bufferOffset = 0;
    int bufferRemaining = 0;

    long nextRecord = 0;

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
     * @param bufferStartOffset    the offset into the buffer where we will stage the data in memory
     * @param bufferLength         the amount of space in the buffer that we can use to stage data
     * @param transferBuffer       the buffer that we temporarily use to read a block from HDD and write back to SSD.
     * @param transferStartOffset  the offset into the buffer used for the temporary transfer
     * @param transferLength       the length of the transfer buffer (should equal stagingLength+bufferLength)
     */
    StagingConfig cfg();

    StagedProvider(StagingConfig cfg);

    Record* next();

    int minSize(long size1, long size2);
};


#endif //CS764_SORTER_STAGEDPROVIDER_H