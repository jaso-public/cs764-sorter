#include "StorageProvider.h"

/**
 * This class is used to read chunks from the SSD
 */
StorageProvider::StorageProvider(unique_ptr<StorageConfig> &config) {
    cfg = std::move(config);

    storageOffset = cfg->startOffset;
    storageRemaining = cfg->recordCount * Record::getRecordSize();

    bufferOffset = 0;
    bufferRemaining = 0;

    totalRecordsReturned = 0;
}

/**
 * Gets the next record from the SSD chunk
 * @returns a pointer to the next record or a null pointer if a next record doesn't exist
 */
shared_ptr<Record> StorageProvider::next() {
    if(totalRecordsReturned >= cfg->recordCount) return nullptr;

    int recordSize = Record::getRecordSize();
    unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(recordSize);

    int recordRemaining = recordSize;
    int recordOffset = 0;

    while(true) {
        if(recordRemaining < 1) {
            totalRecordsReturned++;
            return make_shared<Record>(data);
        }

        if(bufferRemaining < 1) {
            //need to get more bytes from storage
            int sizeToRead = cfg->bufferLength;
            if(storageRemaining < sizeToRead) sizeToRead = storageRemaining;
            int count = cfg->storage->read(storageOffset, cfg->buffer, sizeToRead);
            if(count != sizeToRead) {
                cerr <<"Error in storage provider\n";
                exit(1);
            }
            storageOffset += sizeToRead;
            storageRemaining -= sizeToRead;
            bufferOffset = 0;
            bufferRemaining = sizeToRead;
        }

        int sizeToCopy = recordRemaining;
        if(bufferRemaining < sizeToCopy) sizeToCopy = bufferRemaining;
        memcpy(data.get() + recordOffset, cfg->buffer + bufferOffset, sizeToCopy);
        recordOffset += sizeToCopy;
        recordRemaining -= sizeToCopy;
        bufferOffset += sizeToCopy;
        bufferRemaining -= sizeToCopy;
    }
}
