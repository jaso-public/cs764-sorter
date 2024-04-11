#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "Provider.h"


DeviceProvider::DeviceProvider(shared_ptr<IODevice> _device, int _bufferSize) {
    device = _device;
    deviceOffset = 0;
    bufferSize = _bufferSize;
    bufferOffset = _bufferSize;
    bufferRemaining = 0;
    buffer = std::make_unique<uint8_t[]>(bufferSize);
    eofReached = false;
}

shared_ptr<Record> DeviceProvider::next() {
    if(eofReached) return nullptr;

    int recordSize = Record::getRecordSize();
    int remaining = recordSize;
    int offset = 0;
    auto bytes = std::make_unique<uint8_t[]>(recordSize);

    while(remaining>0) {
        if(bufferRemaining == 0) {
            bufferOffset = 0;
            bufferRemaining = device->read(deviceOffset, buffer.get(), bufferSize);
            if (bufferRemaining == 0) {
                eofReached = true;
                if (offset != 0) {
                    cerr << "end of file reached with partial record offset:" << offset << endl;
                    return nullptr;
                }
            }
        }

        int bytesToMove = bufferRemaining - bufferOffset;
        if(bytesToMove > remaining) bytesToMove = remaining;
        memcpy(bytes.get()+offset, buffer.get()+bufferOffset, bytesToMove);
        bufferRemaining -= bytesToMove;
        bufferOffset += bytesToMove;
        remaining -= bytesToMove;
        offset += bytesToMove;
     }

    return make_shared<Record>(buffer);
}

