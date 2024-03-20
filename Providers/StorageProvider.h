#ifndef CS764_SORTER_STORAGEPROVIDER_H
#define CS764_SORTER_STORAGEPROVIDER_H
#include "IODevice.h"
#include "./Records/Record.h"
#include "Provider.h"

class StorageProvider: public Provider{
private:
    int recordSize;
    long recordCount;
    uint32_t keyOffset;

    IODevice storage;
    long storageStartOffset;

    char * buffer;
    int bufferStartOffset;
    int bufferLength;



    int bufferOffset = 0;
    int bufferRemaining = 0;

    long storageOffset = 0;
    long storageRemaining = 0;

    long nextRecord = 0;

public:
    StorageProvider(
            int recordSize,
            long recordCount,
            IODevice storage,
            long storageStartOffset,
            char * buffer,
            int bufferStartOffset,
            int bufferLength,     uint32_t keyOffset);

    Record* next();

};


#endif //CS764_SORTER_STORAGEPROVIDER_H
