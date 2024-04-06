#ifndef CS764_SORTER_STORAGEPROVIDER_H
#define CS764_SORTER_STORAGEPROVIDER_H
#include "Record.h"
#include "Provider.h"

#include "Config/SorterConfig.h"
#include "../src/IODevice.h"

class StorageProvider: public Provider{
private:
    SorterConfig* cfg;
    string filepath;

    IODevice storage;
    long storageStartOffset;

    uint8_t *buffer;
    int bufferStartOffset;
    int bufferLength;

    int bufferOffset;
    int bufferRemaining;

    long storageOffset;
    long storageRemaining;

    long nextRecord;

public:
    StorageProvider(
            IODevice* storage,
            long storageStartOffset,
            uint8_t *buffer,
            int bufferStartOffset,
            int bufferLength, SorterConfig cfg);

    shared_ptr<Record> next() override;

};


#endif //CS764_SORTER_STORAGEPROVIDER_H
