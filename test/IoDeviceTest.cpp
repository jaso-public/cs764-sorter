#include <assert.h>
#include <iostream>

#include "IODevice.h"


void testRead() {
    IODevice i("/tmp/test.txt");
    uint8_t* buffer = new uint8_t[10];
    // first put some data in the file
    i.write(0, buffer, 10);

    i.read(0, buffer, 5);
    assert("Read count should be one" && i.getReadCount() == 1 );
    assert("Read size should be 5" && i.getReadSize() == 5 );
    i.read(5, buffer, 5);
    assert("Read count should be 2" && i.getReadCount() == 2 );
    assert("Read size should be 10" && i.getReadSize() == 10 );
}

void testWrite() {
    IODevice i("/tmp/test.txt");
    uint8_t* buffer = new uint8_t[5];
    buffer[0]= 8;
    buffer[1]= 8;
    buffer[2]= 8;
    buffer[3]= 8;
    buffer[4]= 8;
    i.write(0, buffer, 5);
    assert("Write count should be one" && i.getWriteCount() == 1 );
    assert("Write size should be 5" && i.getWriteSize() == 5 );
}

int main(){
    testRead();
    testWrite();
}