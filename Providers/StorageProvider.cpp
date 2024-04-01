#include "StorageProvider.h"

StorageProvider::StorageProvider(int recordSize, long recordCount, IODevice storage, long storageStartOffset,
                                 uint8_t *buffer, int bufferStartOffset, int bufferLength, uint32_t keyOffset, uint32_t keySize):storage("") {
    this->recordSize = recordSize;
    this->recordCount = recordCount;
    this->keySize = keySize;
    this->storageStartOffset = storageStartOffset;
    this->buffer = buffer;
    this->bufferStartOffset = bufferStartOffset;
    this->bufferLength = bufferLength;
    this->storage=storage;
    this->keyOffset = keyOffset;
    this->storageRemaining = recordCount * (long)recordSize;
    this->bufferOffset = 0;
    this->bufferRemaining = 0;
    this->storageOffset = 0;
    this->storageRemaining = 0;
    this->nextRecord = 0;
}

shared_ptr<Record> StorageProvider::next() {
    if(nextRecord >= recordCount) return nullptr;
    void* data = new char[recordSize];
    int recordRemaining = recordSize;
    int recordOffset = 0;

    while(true) {
        if(recordRemaining < 1) {
            nextRecord++;
            nextRecord++;
            Record::staticInitialize(recordSize, keyOffset, keySize);
            shared_ptr<Record> ptr(new Record);
            return ptr;
        }

        if(bufferRemaining < 1) {
            //need to get more bytes from storage
            int sizeToRead = bufferLength;
            if(storageRemaining < sizeToRead) sizeToRead = (int)storageRemaining;
            storage.read(storageStartOffset + storageOffset, buffer, bufferStartOffset, sizeToRead);
            storageOffset += sizeToRead;
            storageRemaining -= sizeToRead;
            bufferOffset = 0;
            bufferRemaining = sizeToRead;
        }

        int sizeToCopy = recordRemaining;
        if(bufferRemaining < sizeToCopy) sizeToCopy = bufferRemaining;
        // move pointers to point to correct destination in destination and source
        void *source = &buffer + bufferStartOffset + bufferOffset;
        void *destination = &data + recordOffset;
        memcpy(destination, source, sizeToCopy);
        recordOffset += sizeToCopy;
        recordRemaining -= sizeToCopy;
        bufferOffset += sizeToCopy;
        bufferRemaining -= sizeToCopy;
    }
}
