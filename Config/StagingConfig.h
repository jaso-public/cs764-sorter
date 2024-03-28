#ifndef CS764_SORTER_STAGINGCONFIG_H
#define CS764_SORTER_STAGINGCONFIG_H
#include "IODevice.h"


class StagingConfig {
public:
    uint64_t recordSize;
    uint32_t keyOffset;
    long recordCount;
    long storageStartOffset;
    long stagingStartOffset;
    long stagingLength;
    uint8_t *buffer;
    int bufferStartOffset;
    int bufferLength;
    uint8_t *transferBuffer;
    int transferStartOffset;
    int transferLength;
    IODevice storage;
    IODevice staging;
    StagingConfig();
};


#endif //CS764_SORTER_STAGINGCONFIG_H
