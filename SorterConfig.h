#ifndef CS764_SORTER_SORTERCONFIG_H
#define CS764_SORTER_SORTERCONFIG_H
#include "IODevice.h";

/**
 * This is the configuration file utilized to aid in sorting records
 * Defines all variables that are required for sorting
 */
class SorterConfig {
public:
    float fraction = 0.005F;
    int memoryBlockSize = 1024 * 1024;
    int memoryBlockCount = 100;

    IODevice ssdDevice;
    int ssdReadSize = 16 * 1024;
    long ssdStorageSize = 10L * 1024 * 1024 * 1024;

    IODevice hddDevice;
    int hddReadSize = 256 * 1024;

    /**
     * Class constructor that will initialize the IODevices with the right files
     */
    SorterConfig();
};


#endif //CS764_SORTER_SORTERCONFIG_H
