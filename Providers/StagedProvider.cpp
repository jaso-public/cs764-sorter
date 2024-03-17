#include "StagedProvider.h"
#include "../StagingConfig.h"
#include <assert.h>

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
StagedProvider::StagedProvider(StagingConfig cfg):storage("test"), staging("test") {
    this->recordSize = cfg.recordSize;
    this->recordCount = cfg.recordCount;
    this->storageStartOffset = cfg.storageStartOffset;
    this->stagingStartOffset = cfg.stagingStartOffset;
    this->stagingLength = cfg.stagingLength;
    this->buffer = cfg.buffer;
    this->bufferStartOffset = cfg.bufferStartOffset;
    this->bufferLength = cfg.bufferLength;
    this->transferBuffer = cfg.transferBuffer;
    this->transferStartOffset = cfg.transferStartOffset;

    assert(cfg.transferLength >= bufferLength + stagingLength);

    assert(cfg.bufferStartOffset + cfg.bufferLength <= sizeof(cfg.buffer));

    storageRemaining = recordCount * (long)recordSize;
}

/**
 *
 * @return a pointer to the next record or a null pointer if all records have been generated
 */
Record* StagedProvider::next() {
    if (nextRecord >= recordCount) return nullptr;
    uint64_t *data = new uint64_t[recordSize];
    int recordRemaining = recordSize;
    int recordOffset = 0;
    //TODO: ending here
    while(true){
        if(recordRemaining < 1) {
            nextRecord++;
            Record r(data);

            return ;
        }
    }
}
