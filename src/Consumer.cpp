#include "Consumer.h"


DeviceConsumer::DeviceConsumer(shared_ptr<Provider> _source, shared_ptr<IODevice> _device, int _bufferSize) {
    source = _source;
    outputDevice = _device;
    deviceOffset = 0;
    bufferSize = _bufferSize;
    bufferOffset = 0;
    buffer = std::make_unique<uint8_t[]>(bufferSize);
}

void DeviceConsumer::consume() {
    while(true) {
        shared_ptr<Record> ptr = source->next();
        if(ptr == nullptr) break;
        appendRecord(ptr);
    }
    doWrite(); // flush any pending data
}

void DeviceConsumer::appendRecord(shared_ptr<Record> &ptr) {
    int offset = 0;
    int remaining = Record::getRecordSize();

    while(remaining>0) {
        int bytesToMove = bufferSize - bufferOffset;
        if(bytesToMove > remaining) bytesToMove = remaining;
        ptr->store(buffer.get() + bufferOffset, offset, bytesToMove);
        bufferOffset += bytesToMove;
        offset += bytesToMove;
        remaining -= bytesToMove;
        if(bufferOffset==bufferSize) doWrite();
    }
}

void DeviceConsumer::doWrite() {
    if(bufferOffset == 0) return;
    outputDevice->write(deviceOffset, buffer.get(), bufferOffset);
    deviceOffset += bufferOffset;
    bufferOffset = 0;
}
