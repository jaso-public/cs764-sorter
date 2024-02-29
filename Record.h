#ifndef DB_RECORD_H
#define DB_RECORD_H
#include <stdint.h>

class Record {
public:
    // size of the record
    int size;
    // key offset of record
    uint32_t keyOffset;
    // created record
    void* record;
    // record constructor
    Record(int sizeFromUser,  uint32_t keyOffsetFromUser);

    /**
     * This method obtains the key from a given record
     * @return record's key
     */
    uint64_t getRecordKey();
    /**
     * This method will check if r1's key is the same as r2's to ensure that the key did not change during sort
     * @param r1 the record prior to manipulation
     * @param r2 the record after manipulation
     * @param keyOffset the offset value used to find the key location
     * @returns true if r2 checksum is 0; else returns false
     */
    bool completeChecksumCheck();

private:
    /**
    * This method will create a record in memory and fill it with random 64 bit integers
    * @return void* array as the created record
    */
    void* createRecord();
};


#endif //DB_RECORD_H
