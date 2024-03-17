#ifndef CS764_SORTER_STAGINGCONFIG_H
#define CS764_SORTER_STAGINGCONFIG_H
#include "IODevice.h"


class StagingConfig {
public:
    int recordSize;
    long recordCount;
    long storageStartOffset;
    long stagingStartOffset;
    long stagingLength;
    void *buffer;
    int bufferStartOffset;
    int bufferLength;
    void *transferBuffer;
    int transferStartOffset;
    int transferLength;
};


#endif //CS764_SORTER_STAGINGCONFIG_H
