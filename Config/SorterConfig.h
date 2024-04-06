#ifndef CS764_SORTER_SORTERCONFIG_H
#define CS764_SORTER_SORTERCONFIG_H
#include "../src/IODevice.h"

/**
 * This is the configuration file utilized to aid in sorting records
 * Defines all variables that are required for sorting
 */
class SorterConfig {
public:
    float fraction;
    int memoryBlockSize;
    int memoryBlockCount;

    IODevice ssdDevice;
    int ssdReadSize;
    long ssdStorageSize;

    IODevice hddDevice;
    int hddReadSize;

    uint32_t recordSize;
    uint32_t keyOffset;
    uint32_t keySize;
    long recordCount;


    /**
     * Class constructor that will initialize the IODevices with the right files
     */
    SorterConfig();
};


#endif //CS764_SORTER_SORTERCONFIG_H
