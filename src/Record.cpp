#include "Record.h"

// initialize the global values for the record parameters
uint32_t Record::recordSize = 64;
uint64_t Record::compareCount = 0;

void Record::staticInitialize(uint32_t _recordSize) {
    recordSize = _recordSize;
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

    data = std::move(newData);
}

int Record::compareTo(const shared_ptr<Record> &other) {
    compareCount++;
    return memcmp(this->data.get(), other->data.get(), recordSize);
}

void Record::store(uint8_t *dst) {
    memcpy(dst, data.get(), recordSize);
}

void Record::store(uint8_t *dst, int offset, int numToCopy) {
    memcpy(dst, data.get() + offset, numToCopy);
}

void Record::dump(string message) {
    cout << message << " ";
    for (int i = 0; i < recordSize; i++) {
        printf("%c", data[i]);
    }
    cout << " checksum:" << checksum() << endl;
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
