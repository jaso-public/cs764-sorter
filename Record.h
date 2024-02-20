#ifndef DB_RECORD_H
#define DB_RECORD_H
#include <stdint.h>

class Record {
    /**
     * This method will create a record in memory and fill it with random 64 bit integers
     * @param size the size of the record
     * @return void* array as the created record
     */
    void* createRecord(int size);
    /**
     * This method obtains the key from a given record
     * @param record the record to get the key from
     * @param keyOffset the offset value used to find the key location
     * @return record's key
     */
    uint64_t getRecordKey(void* record, uint32_t keyOffset);
    /**
     * This method will check if r1's key is the same as r2's to ensure that the key did not change during sort
     * @param r1 the record prior to manipulation
     * @param r2 the record after manipulation
     * @param keyOffset the offset value used to find the key location
     * @returns true if r2 checksum is 0; else returns false
     */
    bool completeChecksumCheck(void* r1, void* r2, uint32_t keyOffset);
    /**
      * This method compares two records' keys to see which one is greater
       * @param r1 is the first record for comparison
       * @param r2 is the second record for comparison
       * @returns 1 if r1's key > r2's key2, -1 if r1's key1 < r2's key2, or 0 if both keys are equal
      */
    int compareRecordKeys(void* r1, void* r2, uint32_t keyOffset);
};


#endif //DB_RECORD_H
