#include "Record.h"

// initialize the global values for the record parameters
uint32_t Record::recordSize = 64;
uint32_t Record::keySize = 12;
uint32_t Record::keyOffset = 10;
uint64_t Record::compareCount = 0;

void Record::staticInitialize(uint32_t _recordSize, uint32_t _keyOffset, uint32_t _keySize) {
    recordSize = _recordSize;
    keyOffset = _keyOffset;
    keySize = _keySize;
    compareCount = 0;
}

// TODO remove this constructor
Record::Record() {
    data = new uint8_t[recordSize];
}

Record::Record(uint8_t *newData) {
    data = new uint8_t[recordSize];
    set(newData);
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

int Record::compareTo(const shared_ptr<Record> other) {
    compareCount++;
    return memcmp(data + keyOffset, other->data + keyOffset, keySize);
}

bool Record::isDuplicate(const shared_ptr <Record> other) {
    return memcmp(this->data, other->data, recordSize) == 0;
}

void Record::store(uint8_t *dst) {
    memcpy(dst, data, recordSize);
}

void Record::store(uint8_t *dst, int offset, int numToCopy) {
    memcpy(dst, data + offset, numToCopy);
}

// TODO get rid of this method -- just use the constructor
void Record::set(uint8_t *src) {
    memcpy(data, src, recordSize);
}

// TODO get rid of this method -- just use the constructor
void Record::set(uint8_t *src, int offset, int numToCopy) {
    memcpy(data + offset, src, numToCopy);
}

// TODO compute a real crc32
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
