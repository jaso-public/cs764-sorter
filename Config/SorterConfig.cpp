#include "SorterConfig.h"

/**
 * Class constructor that will initialize the IODevices with the right files
 */
SorterConfig::SorterConfig()
    : hddDevice("hddStaging.tmp"), ssdDevice("ssdStaging.tmp")
{
}