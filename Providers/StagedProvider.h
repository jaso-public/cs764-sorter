#ifndef CS764_SORTER_STAGEDPROVIDER_H
#define CS764_SORTER_STAGEDPROVIDER_H


#include "IODevice.h"
#include "Provider.h"
#include "StagingConfig.h"

class StagedProvider:Provider {
private:
    int recordSize;
    long recordCount;

    IODevice storage;
    long storageStartOffset;

    IODevice staging;
    long stagingStartOffset;
    long stagingLength;

    char * bufferPtr;
    int bufferStartOffset;
    int bufferLength;

    char * transferBuffer;
    int transferStartOffset;

    long storageOffset = 0;
    long storageRemaining = 0;

    long stagingOffset = 0;
    long stagingRemaining;

    int bufferOffset = 0;
    int bufferRemaining = 0;

    long nextRecord = 0;

public:
    StagedProvider(StagingConfig cfg);

    Record* next();

    int minSize();

};


#endif //CS764_SORTER_STAGEDPROVIDER_H
