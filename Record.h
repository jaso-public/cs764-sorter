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
    * This method compare two record's keys to see which one is great
     * @param r1 is the first record for comparison
     * @param r2 is the second record for comparison
     * @returns 1 if r1's key > r2's key2, -1 if r1's key1 < r2's key2, or 0 if both keys are equal
    */
    int compareRecordKeys(void* r1, void* r2, uint32_t keyOffset);
};


#endif //DB_RECORD_H
