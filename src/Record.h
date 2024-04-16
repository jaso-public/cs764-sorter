#pragma once

#include <iostream>
#include <cstring>
#include <memory>

using namespace std;


class Record {
public:
    /**
     * Sets the class' static variables
     * @param _recordSize the size of each record
     */
    static void staticInitialize(uint32_t recordSize);

    /**
     * Stores the given record into the class' record variable (data)
     * @param newData given record
     */
    Record(unique_ptr<uint8_t[]> &newData);

    /**
     * This method compares the class' record to the given record (other)
     * @param other the record to compare with the class' record
     * @return 1 if other is smaller than the class' record, 0 if the two records or equal, or false
     */
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

    void dump(string message);

    static uint32_t getRecordSize() {return recordSize;}
    static uint64_t getCompareCount() {return compareCount;}
    static void resetCompareCount() {compareCount = 0;}

private:
    static uint32_t recordSize;   // size of the record
    static uint64_t compareCount; // the number of compares that occurred between the record
    unique_ptr<uint8_t[]> data;   // the actual bytes of the record
};
