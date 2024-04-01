#include "IoDeviceTest.h"
#include <iostream>

void IoDeviceTest::testRead() {
    IODevice i("../Testing/Tests/IODevice/test.txt");
    uint8_t* buffer = new uint8_t[5];
    i.read(0, buffer, 0, 5);
    assert("Read count should be one" && i.getReadCount() == 1 );
    assert("Read size should be 5" && i.getReadSize() == 5 );
    i.read(5, buffer, 0, 5);
    assert("Read count should be 2" && i.getReadCount() == 2 );
    assert("Read size should be 10" && i.getReadSize() == 10 );
    i.close();
}

void IoDeviceTest::testWrite() {
    IODevice i("../Testing/Tests/IODevice/test.txt");
    uint8_t* buffer = new uint8_t[5];
    i.write(0, buffer, 0, 5);
    assert("Write count should be one" && i.getWriteCount() == 1 );
    assert("Write size should be 5" && i.getWriteSize() == 5 );
}

int main(){
    IoDeviceTest test;
    test.testRead();
    test.testWrite();
}