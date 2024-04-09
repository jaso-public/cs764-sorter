#pragma once

#include <iostream>
#include <cstring>

using namespace std;

class Record {
public:
    static void staticInitialize(uint32_t _recordSize, uint32_t _keyOffset, uint32_t _keySize);

    Record(unique_ptr<uint8_t[]> &newData);

    int compareTo(const shared_ptr<Record> &other);

    bool isDuplicate(const shared_ptr<Record> &other);

    void store(uint8_t *dst);

    void store(uint8_t *dst, int offset, int numToCopy);

    uint64_t checksum();

    void dump() {
        cout << "record:";
        for(int i=0; i<5 ; i++) {
            cout << (int)data[i] << " ";
        }
        cout << endl;
    }

    static uint32_t getRecordSize() {return recordSize;}
    static uint32_t getKeySize() {return keySize;}
    static uint32_t getKeyOffset() {return keyOffset;}

    static uint64_t getCompareCount() {return compareCount;}
    static void resetCompareCount() {compareCount = 0;}

private:
    static uint32_t recordSize;   // size of the record
    static uint32_t keySize;      // the size of the key
    static uint32_t keyOffset;    // key offset inside the record
    static uint64_t compareCount; // the number of compares that
    unique_ptr<uint8_t[]> data;   // the actual bytes of the record
};
