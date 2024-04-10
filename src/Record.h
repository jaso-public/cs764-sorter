#pragma once

#include <iostream>
#include <cstring>

using namespace std;


template<typename T>
bool operator==(const std::shared_ptr<T>& ptr1, const std::shared_ptr<T>& ptr2) {
    // Check if both shared_ptr instances are pointing to the same object or are null
    return (!ptr1 && !ptr2) || (ptr1 && ptr2 && *ptr1 == *ptr2);
}

template<typename T>
bool operator!=(const std::shared_ptr<T>& ptr1, const std::shared_ptr<T>& ptr2) {
    // Check if both shared_ptr instances are pointing to the same object or are null
    return (!ptr1 && !ptr2) || (ptr1 && ptr2 && *ptr1 != *ptr2);
}

template<typename T>
bool operator<=(const std::shared_ptr<T>& ptr1, const std::shared_ptr<T>& ptr2) {
    // Check if both shared_ptr instances are pointing to the same object or are null
    return (!ptr1 && !ptr2) || (ptr1 && ptr2 && *ptr1 <= *ptr2);
}


class Record {
public:
    static void staticInitialize(uint32_t _recordSize, uint32_t _keyOffset, uint32_t _keySize);

    Record(unique_ptr<uint8_t[]> &newData);


    int compareTo(const shared_ptr<Record> &other);
    bool isDuplicate(const shared_ptr<Record> &other);


    bool operator<(const shared_ptr <Record> &other) {
        cout << "in da operator<\n";
        return memcmp(data.get(), other->data.get(), Record::getRecordSize()) < 0;
    }

    bool operator==(Record &other) {
        cout << "in da operator==\n";
        return memcmp(data.get(), other.data.get(), Record::getRecordSize()) == 0;
    }
    bool operator!=(Record &other) {
        cout << "in da operator!=\n";
        return memcmp(data.get(), other.data.get(), Record::getRecordSize()) != 0;
    }

    bool operator<=(Record &other) {
        cout << "in da operator<=\n";
        return memcmp(data.get(), other.data.get(), Record::getRecordSize()) <= 0;
    }

    void store(uint8_t *dst);

    void store(uint8_t *dst, int offset, int numToCopy);

    uint64_t checksum();

    static uint32_t getRecordSize() {return recordSize;}
    static uint32_t getKeySize() {return keySize;}
    static uint32_t getKeyOffset() {return keyOffset;}

    static uint64_t getCompareCount() {return compareCount;}
    static void resetCompareCount() {compareCount = 0;}

    void dump(string message) {
        cout << message << " ";
        for(int i=0; i<recordSize ; i++) {
            printf("%c", data[i]);
        }
        printf(" checksum:%llu\n", checksum());
    }

private:
    static uint32_t recordSize;   // size of the record
    static uint32_t keySize;      // the size of the key
    static uint32_t keyOffset;    // key offset inside the record
    static uint64_t compareCount; // the number of compares that
    unique_ptr<uint8_t[]> data;   // the actual bytes of the record
};
