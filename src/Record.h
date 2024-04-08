#pragma once

#include <iostream>
#include <cstring>

using namespace std;

class Record {
public:
    static void staticInitialize(uint32_t _recordSize, uint32_t _keyOffset, uint32_t _keySize);

    Record(unique_ptr<uint8_t[]> &newData);

//    Record(uint8_t *_data);

    // Copy constructor
    Record(const Record &other);

    // Copy assignment operator
    Record &operator=(const Record &other);

    // Destructor
    ~Record();

    int compareTo(const shared_ptr<Record> other);

    bool isDuplicate(const shared_ptr<Record> other);

    void store(uint8_t *dst);

    void store(uint8_t *dst, int offset, int numToCopy);

    void set(uint8_t *src);

    void set(uint8_t *src, int offset, int numToCopy);

    uint64_t checksum();

    // these are required to have the mapping in tree sorter work
    bool operator<(const Record& other) const {
        cout << "Record operator< (you don't wanna see this)" << endl;
        return data < other.data;
    }

    bool operator==(const Record& other) const {
        cout << "Record operator== (you don't wanna see this)" << endl;
        return data < other.data;
    }

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
