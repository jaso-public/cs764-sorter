#ifndef DB_RECORD_H
#define DB_RECORD_H
#include <stdint.h>

class Record {
public:
    // size of the record
    uint64_t size;
    // key offset of record
    uint32_t keyOffset;
    // created record
    void* record;
    // record constructor
    Record(uint64_t sizeFromUser,  uint32_t keyOffsetFromUser);

    /**
     * This method obtains the key from a given record
     * @return record's key
     */
    uint64_t getRecordKey();

    /**
    * This method will compute the checksum value of the record
    * @returns the checksum value of the record
    */
    bool completeChecksumCheck();

private:
    /**
    * This method will create a record in memory and fill it with random 64 bit integers
     * It is used to create the record during the initialization of the Record constructor
    * @return void* array as the created record
    */
    void* createRecord();
};


#endif //DB_RECORD_H
