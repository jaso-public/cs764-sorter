#pragma once

#include "Record.h"
#include "Provider.h"

#include "IODevice.h"

class StorageProvider: public Provider{
public:
    StorageProvider(shared_ptr<StorageConfig> cfg);
    shared_ptr<Record> next() override;

private:
    shared_ptr<StorageConfig> cfg;

    int bufferOffset;
    int bufferRemaining;

    long storageOffset;
    long storageRemaining;

    long nextRecord;
};

class StorageConfig {
    shared_ptr<IODevice> storage = nullptr;
    long storageStartOffset;
    uint8_t *buffer;
    int bufferStartOffset;
    int bufferLength;
};


#endif //CS764_SORTER_STORAGEPROVIDER_H
