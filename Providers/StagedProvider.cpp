#include "StagedProvider.h"
#include <iostream>
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
  * @param bufferStartOffset    the offset into the buffer where we will stage the data in memory
  * @param bufferLength         the amount of space in the buffer that we can use to stage data
  * @param transferBuffer       the buffer that we temporarily use to read a block from HDD and write back to SSD.
  * @param transferStartOffset  the offset into the buffer used for the temporary transfer
  * @param transferLength       the length of the transfer buffer (should equal stagingLength+bufferLength)
  */
StagedProvider::StagedProvider(StagingConfig cfg): storage(""), staging("") {
    this->recordSize = cfg.recordSize;
    this->keyOffset = cfg.keyOffset;
    this->keySize = cfg.keySize;
    this->storage = cfg.storage;
    this->staging = cfg.staging;
    this->recordCount = cfg.recordCount;
    this->storageStartOffset = cfg.storageStartOffset;
    this->stagingStartOffset = cfg.stagingStartOffset;
    this->stagingLength = cfg.stagingLength;
    this->buffer = cfg.buffer;
    this->bufferStartOffset = cfg.bufferStartOffset;
    this->bufferLength = cfg.bufferLength;
    this->transferBuffer = cfg.transferBuffer;
    this->transferStartOffset = cfg.transferStartOffset;
    this->storageOffset = 0;
    this->storageRemaining = 0;
    this->stagingOffset = 0;
    this->bufferOffset = 0;
    this->bufferRemaining = 0;
    this->nextRecord = 0;

    assert(cfg.transferLength >= bufferLength + stagingLength);

    assert(cfg.bufferStartOffset + cfg.bufferLength <= sizeof(cfg.buffer));

    storageRemaining = recordCount * (long)recordSize;
}

/**
 * @return a pointer to the next record or a null pointer if all records have been generated
 */
shared_ptr<Record> StagedProvider::next() {
    if (nextRecord >= recordCount) return nullptr;
    int recordRemaining = recordSize;
    int recordOffset = 0;
    while (true) {
        if (recordRemaining < 1) {
            nextRecord++;
            Record::staticInitialize(recordSize, keyOffset, keySize);
            shared_ptr<Record> ptr(new Record);
            return ptr;
        }
        if (bufferRemaining < 1) {
            if (stagingRemaining < 1) {
                int sizeToRead = minSize(bufferLength + stagingLength, storageRemaining);
                storage.read(storageStartOffset + storageOffset, transferBuffer, transferStartOffset, sizeToRead);
                storageOffset += sizeToRead;
                storageRemaining -= sizeToRead;

                if (sizeToRead <= bufferLength) {
                    // this must be the final chunk on the HDD.
                    // It is small enough to fit in the buffer.
                    const int arr_size = 10;

                    // move pointers to point to correct destination in destination and source
                    void *source = &transferBuffer + transferStartOffset;
                    void *destination = &buffer + bufferStartOffset;
                    memcpy(destination, source, sizeToRead);
                    stagingOffset = 0;
                    stagingRemaining = 0;
                    bufferOffset = 0;
                    bufferRemaining = sizeToRead;
                } else {
                    // we need to put the beginning of the transfer buffer into our buffer,
                    // and the rest of the data needs to be written to the staging area
                    // move pointers to point to correct destination in destination and source
                    void *destination = &buffer + bufferStartOffset;
                    void *source = &transferBuffer + transferStartOffset;
                    memcpy(destination, source, bufferLength);
                    staging.write(stagingStartOffset, transferBuffer, transferStartOffset + bufferLength,
                                  sizeToRead - bufferLength);
                    stagingOffset = 0;
                    stagingRemaining = sizeToRead - bufferLength;
                    bufferOffset = 0;
                    bufferRemaining = bufferLength;
                }
            } else {
                // there is data available in the staging area, lets read it.
                int sizeToRead = minSize(bufferLength, stagingRemaining);
                staging.read(stagingStartOffset + stagingOffset, buffer, bufferStartOffset, sizeToRead);
                stagingOffset += sizeToRead;
                stagingRemaining -= sizeToRead;
                bufferOffset = 0;
                bufferRemaining = sizeToRead;
            }
            }
        int sizeToCopy = minSize(recordRemaining, bufferRemaining);
        void* data = new uint8_t[recordSize];
        void *destination = &data + recordOffset;
        void *source = &buffer + bufferStartOffset + bufferOffset;
        memcpy(destination, source, sizeToCopy);
        recordOffset += sizeToCopy;
        recordRemaining -= sizeToCopy;
        bufferOffset += sizeToCopy;
        bufferRemaining -= sizeToCopy;
    }
}

int StagedProvider::minSize(long size1, long size2){
    long result = std::min(size1, size2);
    try{
            if(result>INT_MAX) throw (result);
    } catch (long failedResult){
        cout << "Conversion from long to int failed; a long was too large\n";
    }
    return  static_cast<int> (result);;
}