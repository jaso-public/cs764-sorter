#include "Record.h"

uint32_t Record::recordSize = 0;
uint32_t Record::keySize = 0;
uint64_t Record::compareCount = 0;
uint32_t Record::keyOffset = 0;

void Record::staticInitialize(uint32_t _recordSize, uint32_t _keyOffset, uint32_t _keySize) {
    recordSize = _recordSize;
    keyOffset = _keyOffset;
    keySize = _keySize;
    compareCount = 0;
}

Record::Record() {
    data = new uint8_t[recordSize];
}

Record::Record(uint8_t *_data) {
    data = new uint8_t[recordSize];
    set(_data);
}

// Copy constructor
Record::Record(const Record &other) {
    cout << "copy constructor (you don't wanna see this)" << endl;
    data = new uint8_t[recordSize];
    set(other.data);
}

// Copy assignment operator
Record &Record::operator=(const Record &other) {
    cout << "assignment operator (you don't wanna see this)" << endl;
    if (this != &other) {
        delete[] data;
        data = new uint8_t[recordSize];
        set(other.data);
    }
    return *this;
}

Record::~Record() {
    delete[] data;
}

int Record::compareTo(shared_ptr<Record> other) {
    compareCount++;
    return memcmp(data + keyOffset, other->data + keyOffset, keySize);
}

void Record::store(uint8_t *dst) {
    memcpy(dst, data, recordSize);
}

void Record::store(uint8_t *dst, int offset, int numToCopy) {
    memcpy(dst, data + offset, numToCopy);
}

void Record::set(uint8_t *src) {
    memcpy(data, src, recordSize);
}

void Record::set(uint8_t *src, int offset, int numToCopy) {
    memcpy(data + offset, src, numToCopy);
}

uint64_t Record::checksum() {
    int extra = recordSize & 7;
    int num = recordSize >> 3;

    uint64_t result = 0;
    uint64_t *a = (uint64_t *) data;
    for (int i = 0; i < num; i++) {
        result = result ^ a[i];
    }

    if (extra) {
        uint64_t tmp = 0;
        void *ending = a + num;
        memcpy(&tmp, ending, extra);
        result ^= tmp;
    }

    return result;
}

uint64_t Record::getCompareCount() {
    return compareCount;
}

void Record::resetCompareCount() {
    this->compareCount = 0;
}

bool Record::isDuplicate(shared_ptr<Record> other) {
    Record otherRecord = *other;
    uint8_t* otherData = other->data;
    for (int i = 0; i < recordSize; i++){
       if (data[i] != otherData[i]){
           return false;
       }
    }
    return true;
}
