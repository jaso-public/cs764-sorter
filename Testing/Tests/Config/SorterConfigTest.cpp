#include "SorterConfigTest.h"

void SorterConfigTest::testInitialization() {
    SorterConfig config;
    assert("Fraction was not right" && config.fraction ==  0.005F );
    assert("memoryBlockSize was not right" && config.memoryBlockSize == 1024 * 1024 );
    assert("memoryBlockCount was not right" && config.memoryBlockCount ==  100 );
    assert("ssdReadSize was not right" && config.ssdReadSize ==  16 * 1024);
    assert("ssdStorageSize was not right" && config.ssdStorageSize == 10L * 1024 * 1024 * 1024);
    assert("hddReadSize was not right" && config.hddReadSize ==  256 * 1024 );
    assert("Could not access ssdDevice" && config.ssdDevice.getReadSize() ==  0 );
    assert("Could not access hddDevice" && config.hddDevice.getReadSize() ==  0 );
}

int main(){
    SorterConfigTest test;
    test.testInitialization();
}