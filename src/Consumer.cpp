#include "Consumer.h"


FileConsumer::FileConsumer(shared_ptr<Provider> _source, shared_ptr<IODevice> _device, int _bufferSize) {
    source = _source;
    outputDevice = _device;
    deviceOffset = 0;
    bufferSize = _bufferSize;
    bufferOffset = 0;
    buffer = std::make_unique<uint8_t[]>(bufferSize);
}

FileConsumer::~FileConsumer() {
    doWrite(); // flush any pending data
}

void FileConsumer::consume() {
    while(true) {
        shared_ptr<Record> ptr = source->next();
        if(ptr == nullptr) break;
        appendRecord(ptr);
    }
    doWrite();
}

void FileConsumer::appendRecord(shared_ptr<Record> &ptr) {
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

void FileConsumer::doWrite() {
    if(bufferOffset == 0) return;
    outputDevice->write(deviceOffset, buffer.get(), bufferOffset);
    deviceOffset += bufferOffset;
    bufferOffset = 0;
}
