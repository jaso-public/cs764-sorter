#include "SorterConfig.h"

/**
 * Class constructor that will initialize the IODevices with the right files
 */
SorterConfig::SorterConfig(): ssdDevice("../Files/ssdStaging.tmp"), hddDevice("../Files/hddStaging.tmp")
{
    this->fraction = 0.005F;
    this->memoryBlockSize = 1024 * 1024;
    this->memoryBlockCount = 100;
    this->ssdReadSize = 16 * 1024;
    this->ssdStorageSize = 10L * 1024 * 1024 * 1024;
    this->hddReadSize = 256 * 1024;
    this->keySize = 8;
    this->recordCount = 100;
    this->recordSize = 10;
    this->keyOffset = 8;
}


