#include "StorageProvider.h"

StorageProvider::StorageProvider(unique_ptr<StorageConfig> &config) {
    cfg = std::move(config);

    storageOffset = cfg->startOffset;
    storageRemaining = cfg->recordCount * Record::getRecordSize();

    bufferOffset = 0;
    bufferRemaining = 0;

    nextRecord = 0;
}

shared_ptr<Record> StorageProvider::next() {
    if(nextRecord >= cfg->recordCount) return nullptr;

    int recordSize = Record::getRecordSize();
    unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(recordSize);

    int recordRemaining = recordSize;
    int recordOffset = 0;

    while(true) {
        if(recordRemaining < 1) {
            nextRecord++;

            cout << "storage provider returns record -- nextRecord:" << nextRecord << endl;

            return make_shared<Record>(data);
        }

        if(bufferRemaining < 1) {
            //need to get more bytes from storage
            int sizeToRead = cfg->bufferLength;
            if(storageRemaining < sizeToRead) sizeToRead = storageRemaining;
            int count = cfg->storage->read(storageOffset, cfg->buffer, sizeToRead);
            if(count != sizeToRead) {
                cerr <<"real message\n";
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
