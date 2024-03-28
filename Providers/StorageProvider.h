#ifndef CS764_SORTER_STORAGEPROVIDER_H
#define CS764_SORTER_STORAGEPROVIDER_H
#include "../IODevice.h"
#include "./Records/Record.h"
#include "Provider.h"

class StorageProvider: public Provider{
private:
    string filepath;
    int recordSize;
    long recordCount;
    uint32_t keyOffset;

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
            int recordSize,
            long recordCount,
            IODevice storage,
            long storageStartOffset,
            uint8_t *buffer,
            int bufferStartOffset,
            int bufferLength,
            uint32_t keyOffset);

    Record* next() override;

};


#endif //CS764_SORTER_STORAGEPROVIDER_H
