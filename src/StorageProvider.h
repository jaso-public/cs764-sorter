#pragma once

#include "Record.h"
#include "Provider.h"

#include "IODevice.h"


class StorageConfig {
public:
    StorageConfig() {}

    uint64_t recordCount;
    uint64_t startOffset;

    uint8_t *buffer;
    uint32_t bufferLength;

    shared_ptr<IODevice> storage;
};

class StorageProvider: public Provider{
public:
    StorageProvider(unique_ptr<StorageConfig> &cfg);
    shared_ptr<Record> next() override;

private:
    shared_ptr<StorageConfig> cfg;

    int bufferOffset;
    int bufferRemaining;

    long storageOffset;
    long storageRemaining;

    // TODO give this a better name
    long nextRecord;
};
