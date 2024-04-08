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

Record::Record(unique_ptr<uint8_t[]> &newData) {
    if(newData == nullptr) {
        cerr << "cannot construct a Record with a nullptr" <<endl;
        exit(-1);
    }
    if(newData.get() == nullptr) {
        cerr << "cannot construct a Record with a nullptr" <<endl;
        exit(-1);
    }

    newData = std::move(data);
}


Record::Record(uint8_t *newData) {
    data = make_unique<uint8_t[]>(recordSize);
    memcpy(data.get(), newData, recordSize);
}

// Copy constructor
Record::Record(const Record &other) {
    cout << "copy constructor (you don't wanna see this)" << endl;
    data = std::make_unique<uint8_t[]>(recordSize);
    memcpy(data.get(), other.data.get(), recordSize);
}

// Copy assignment operator
Record &Record::operator=(const Record &other) {
    cout << "assignment operator (you don't wanna see this)" << endl;
    if (this != &other) {
        data = std::make_unique<uint8_t[]>(recordSize);
        memcpy(data.get(), other.data.get(), recordSize);
    }
    return *this;
}

Record::~Record() {}

int Record::compareTo(const shared_ptr<Record> other) {
    compareCount++;
    int result = memcmp(data.get() + keyOffset, other->data.get() + keyOffset, keySize);
    if(result != 0) return result;
    return memcmp(this->data.get(), other->data.get(), recordSize);
}

bool Record::isDuplicate(const shared_ptr <Record> other) {
    return memcmp(this->data.get(), other->data.get(), recordSize) == 0;
}

void Record::store(uint8_t *dst) {
    memcpy(dst, data.get(), recordSize);
}

void Record::store(uint8_t *dst, int offset, int numToCopy) {
    memcpy(dst, data.get() + offset, numToCopy);
}

// TODO compute a real crc32
uint64_t Record::checksum() {
    int extra = recordSize & 7;
    int num = recordSize >> 3;

    uint64_t result = 0;
    uint64_t *a = (uint64_t *) data.get();
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
