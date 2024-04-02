#include "StorageProvider.h"

StorageProvider::StorageProvider(IODevice storage, long storageStartOffset,
                                 uint8_t *buffer, int bufferStartOffset, int bufferLength, SorterConfig cfg):storage("") {
    this->storageStartOffset = storageStartOffset;
    this->buffer = buffer;
    this->bufferStartOffset = bufferStartOffset;
    this->bufferLength = bufferLength;
    this->storage=storage;
    this->storageRemaining = cfg.recordCount * (long)cfg.recordSize;
    this->bufferOffset = 0;
    this->bufferRemaining = 0;
    this->storageOffset = 0;
    this->storageRemaining = 0;
    this->nextRecord = 0;
    this->cfg = &cfg;
}

shared_ptr<Record> StorageProvider::next() {
    if(nextRecord >= cfg->recordCount) return nullptr;
    void* data = new char[cfg->recordSize];
    int recordRemaining = cfg->recordSize;
    int recordOffset = 0;

    while(true) {
        if(recordRemaining < 1) {
            nextRecord++;
            nextRecord++;
            Record::staticInitialize(cfg->recordSize, cfg->keyOffset, cfg->keySize);
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
