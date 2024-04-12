#pragma once

#include <iostream>
#include <cstring>
#include <memory>

using namespace std;


class Record {
public:
    static void staticInitialize(uint32_t recordSize);

    Record(unique_ptr<uint8_t[]> &newData);

    int compareTo(const shared_ptr<Record> &other);

    void store(uint8_t *dst);

    /**
     * stores part of the record into the destination array
     * @param dst the destination where the bytes will be stored
     * @param offset the starting offset in the record from where to begin the transfer
     * @param numToCopy the number of bytes to be moved to the destination
     */
    void store(uint8_t *dst, int offset, int numToCopy);

    uint64_t checksum();


    // TODO remove (eventually)
    void dump(string message) {
        cout << message << " ";
        for(int i=0; i<recordSize ; i++) {
            printf("%c", data[i]);
        }
        printf(" checksum:%lu\n", checksum());
    }

    static uint32_t getRecordSize() {return recordSize;}
    static uint64_t getCompareCount() {return compareCount;}
    static void resetCompareCount() {compareCount = 0;}

private:
    static uint32_t recordSize;   // size of the record
    static uint64_t compareCount; // the number of compares that
    unique_ptr<uint8_t[]> data;   // the actual bytes of the record
};
