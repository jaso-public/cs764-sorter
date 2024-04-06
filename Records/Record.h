#ifndef DB_RECORD_H
#define DB_RECORD_H

#include <iostream>
#include <cstring>

using namespace std;

class Record {
public:
    static void staticInitialize(uint32_t _recordSize, uint32_t _keyOffset, uint32_t _keySize);

    Record();

    Record(uint8_t *_data);

    // Copy constructor
    Record(const Record &other);

    // Copy assignment operator
    Record &operator=(const Record &other);

    // Destructor
    ~Record();

    /**
     * Compares two records' keys together
     * @param other is the other record to compare this record
     * @return 1 if this record is greater
     *         0 if the two keys are equal
     *        -1 if the other key is greater
     */
    int compareTo(Record other);

    bool isDuplicate(Record other);

    void store(uint8_t *dst);

    void store(uint8_t *dst, int offset, int numToCopy);

    void set(uint8_t *src);

    void set(uint8_t *src, int offset, int numToCopy);

    uint64_t checksum();

    // these are required to have the mapping in tree sorter work
    bool operator<(const Record& other) const{
        return data < other.data;
    }

    bool operator==(const Record& other) const{
        return data < other.data;
    }

    static uint32_t getRecordSize() {return recordSize;}
    static uint32_t getKeySize() {return keySize;}
    static uint32_t getKeyOffset() {return keyOffset;}

    static uint64_t getCompareCount() {return compareCount;}
    static void resetCompareCount() {compareCount = 0;}

    // BIG ASS TODO get rid of this and uncomment the data reference
    uint8_t* data;

private:
    static uint32_t recordSize;   // size of the record
    static uint32_t keySize;      // the size of the key
    static uint32_t keyOffset;    // key offset inside the record
    static uint64_t compareCount; // the number of compares that
//    uint8_t* data;                // the actual bytes of the record
};
#endif //DB_RECORD_H