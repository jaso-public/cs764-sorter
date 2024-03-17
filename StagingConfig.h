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
    char * bufferPtr;
    int bufferStartOffset;
    int bufferLength;
    char * transferBuffer;
    int transferStartOffset;
    int transferLength;
    StagingConfig();
};


#endif //CS764_SORTER_STAGINGCONFIG_H
