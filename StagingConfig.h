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
    char * buffer;
    int bufferStartOffset;
    int bufferLength;
    char * transferBuffer;
    int transferStartOffset;
    int transferLength;
};


#endif //CS764_SORTER_STAGINGCONFIG_H
