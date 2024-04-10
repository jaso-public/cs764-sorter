#pragma once

#include <iostream>
#include <cstring>

using namespace std;


class Record {
public:
    static void staticInitialize(uint32_t _recordSize);

    Record(unique_ptr<uint8_t[]> &newData);

    int compareTo(const shared_ptr<Record> &other);

    void store(uint8_t *dst);

    void store(uint8_t *dst, int offset, int numToCopy);

    uint64_t checksum();

    static uint32_t getRecordSize() {return recordSize;}

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
    static uint64_t compareCount; // the number of compares that
    unique_ptr<uint8_t[]> data;   // the actual bytes of the record
};
