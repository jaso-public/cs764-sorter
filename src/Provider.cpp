#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "Provider.h"
#include "Generator.h"

SingleProvider::SingleProvider(): record(nullptr) {}

/**
 * Sets the class record's variable to the given record
 * @param r the new record variable of the class
 */
void SingleProvider::reset(shared_ptr<Record> r) {
    record = r;
}

// returns the class record's variable and then turns it to null
shared_ptr<Record> SingleProvider::next() {
shared_ptr<Record> result = record;
record = nullptr;
return result;
}

MemoryProvider::MemoryProvider(uint8_t *_buffer, uint32_t _recordCount) : buffer(_buffer), recordCount(_recordCount), generatedRecordCount(0) {}

shared_ptr<Record> MemoryProvider::next() {
    if (generatedRecordCount >= recordCount) return nullptr;

    int recordSize = Record::getRecordSize();

    uint32_t offset = generatedRecordCount * recordSize;

    unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(recordSize);
    memcpy(data.get(), buffer + offset, recordSize);

    generatedRecordCount++;
    return make_shared<Record>(data);
}


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

RandomProvider::RandomProvider(int _recordCount, double _duplicateProbability, int _duplicateRange, bool _newLine)
        : recordCount(_recordCount),
          duplicateProbability(_duplicateProbability),
          newLine(_newLine),
          generated(0),
          gen(rd()),  // Seed the main generator
          randomProbability(0.0, 1.0),  // Initialize the probability distribution
          randomRange(0, _duplicateRange)  // Initialize the range distribution with _duplicateRange
{}

RandomProvider::RandomProvider(int _recordCount, bool _newLine): RandomProvider(_recordCount, 0.0, 10, _newLine) {}


shared_ptr<Record> RandomProvider::next() {
    if (generated == recordCount) return nullptr;
    generated++;

    if (randomProbability(gen) < duplicateProbability) {
        duplicateGen.seed(randomRange(gen));
        return makeRandomRecord(duplicateGen, newLine);
    }
    return makeRandomRecord(gen, newLine);
}

