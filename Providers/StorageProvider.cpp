#include "StorageProvider.h"


//TODO: replace out test
StorageProvider::StorageProvider(int recordSize, long recordCount, IODevice storage, long storageStartOffset,
                                 char *buffer, int bufferStartOffset, int bufferLength, uint32_t keyOffset):storage("test") {
    this->recordSize = recordSize;
    this->recordCount = recordCount;
    this->storageStartOffset = storageStartOffset;
    this->buffer = buffer;
    this->bufferStartOffset = bufferStartOffset;
    this->bufferLength = bufferLength;
    this->keyOffset = keyOffset;
    storageRemaining = recordCount * (long)recordSize;
}

Record* StorageProvider::next() {
    if(nextRecord >= recordCount) return nullptr;
    void* data = new char[recordSize];
    int recordRemaining = recordSize;
    int recordOffset = 0;

    while(true) {
        if(recordRemaining < 1) {
            nextRecord++;
            nextRecord++;
            Record r(recordSize, keyOffset);
            Record *ptr = &r;
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