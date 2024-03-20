#include "SorterConfig.h"

/**
 * Class constructor that will initialize the IODevices with the right files
 */
SorterConfig::SorterConfig(){
    IODevice s("test");
    this->ssdDevice = s;

}

IODevice SorterConfig::ssdDevice() {
    return IODevice();
}
