#include "Provider.h"
#include "Generator.h"

/**
 * Initializes the class' record variable to null as it needs to be set by reset() first
*/
SingleProvider::SingleProvider(): record(nullptr) {}

/**
 * Sets the class' record variable to the given record
 * @param r the new record of the class to be returned in the next call to next()
*/
void SingleProvider::reset(shared_ptr<Record> r) {
    record = r;
}

/**
 * Returns the class' record
 * @return the class' record set by reset() or a null pointer if the record has already been returned
*/
shared_ptr<Record> SingleProvider::next() {
    shared_ptr<Record> result = record;
    record = nullptr;
    return result;
}

/**
 * Class constructor that initializes class' variables
 * @param _buffer buffer to extract records from
 * @param _recordCount total number of records to extract
*/
MemoryProvider::MemoryProvider(uint8_t *_buffer, uint32_t _recordCount) : buffer(_buffer), recordCount(_recordCount), generatedRecordCount(0) {}

/**
 * Gets and returns the next record out of the buffer
 * @return a record or a null pointer if all records have been returned
*/
shared_ptr<Record> MemoryProvider::next() {
    if (generatedRecordCount >= recordCount) return nullptr;

    int recordSize = Record::getRecordSize();

    uint32_t offset = generatedRecordCount * recordSize;

    unique_ptr<uint8_t[]> data = make_unique<uint8_t[]>(recordSize);
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
    buffer = make_unique<uint8_t[]>(bufferSize);
    eofReached = false;
}

shared_ptr<Record> DeviceProvider::next() {
    if(eofReached) return nullptr;

    int recordSize = Record::getRecordSize();
    int remaining = recordSize;
    int offset = 0;
    auto bytes = make_unique<uint8_t[]>(recordSize);

    while(remaining>0) {
        if(bufferRemaining == 0) {
            bufferRemaining = device->read(deviceOffset, buffer.get(), bufferSize);
            if (bufferRemaining == 0) {
                if (offset != 0) {
                    cerr << "end of file reached with partial record offset:" << offset << endl;
                }
                eofReached = true;
                return nullptr;
            }
            deviceOffset += bufferRemaining;
            bufferOffset = 0;
        }

        int bytesToMove = bufferRemaining ;
        if(bytesToMove > remaining) bytesToMove = remaining;
        memcpy(bytes.get()+offset, buffer.get()+bufferOffset, bytesToMove);
        bufferRemaining -= bytesToMove;
        bufferOffset += bytesToMove;
        remaining -= bytesToMove;
        offset += bytesToMove;
     }

    return make_shared<Record>(bytes);
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
RandomProvider::RandomProvider(int _recordCount): RandomProvider(_recordCount, 0.0, 10, true) {}


shared_ptr<Record> RandomProvider::next() {
    if (generated >= recordCount) return nullptr;
    generated++;

    if (randomProbability(gen) < duplicateProbability) {
        duplicateGen.seed(randomRange(gen));
        return makeRandomRecord(duplicateGen, newLine);
    }
    return makeRandomRecord(gen, newLine);
}

/**
 * Class constructor that automatically drops the first record
 * @param givenSource the provider to obtain records from
 */
DropFirst::DropFirst(shared_ptr<Provider> _source): source(_source) {
    // sets the given provider to class provider variable and skips first record
    source->next();
}

/**
 * Gets the next record from the provider or a null record
 * @return a pointer to the next record or a null pointer if a next record does not exist
 */
shared_ptr<Record> DropFirst::next() {
    return source->next();
}
