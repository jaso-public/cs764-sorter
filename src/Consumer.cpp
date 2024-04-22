#include "Consumer.h"

/**
 * Class constructor that initializes class variables and creates a buffer of the desired size
 * @param _source the provider to obtain records from
 * @param _device IO device that will write to the output file
 * @param _bufferSize the size of the buffer to store records in
 */
DeviceConsumer::DeviceConsumer(shared_ptr<Provider> _source, shared_ptr<IODevice> _device, int _bufferSize) {
    source = _source;
    outputDevice = _device;
    deviceOffset = 0;
    bufferSize = _bufferSize;
    bufferOffset = 0;
    buffer = make_unique<uint8_t[]>(bufferSize);
}

/**
 * Continues to obtain records from the provider and passes them to the appendRecord() function
 * Flushes the record data once all records have been consumed
 */
void DeviceConsumer::consume() {
    while(true) {
        shared_ptr<Record> ptr = source->next();
        if(ptr == nullptr) {
            cerr << "DeviceConsumer source returned null" << endl;
            break;
        }
        appendRecord(ptr);
    }
    doWrite(); // flush any pending data
}

/**
 * This method will continue to store records into the buffer until the buffer is full
 * Once the buffer is full, it will call doWrite() to write the buffer contents to the particular file
 * @param ptr the next record to write to the buffer
 */
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

/**
 * This method will write the buffer's contents to the file within the IO device
 * It will then reset the buffer offset, so it can store more records
 */
void DeviceConsumer::doWrite() {
    if(bufferOffset == 0) return;
    outputDevice->write(deviceOffset, buffer.get(), bufferOffset);
    deviceOffset += bufferOffset;
    bufferOffset = 0;
}
