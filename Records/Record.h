#ifndef DB_RECORD_H
#define DB_RECORD_H
#include <stdint.h>
#include "../Records/Record.h"

class Record {
public:
    char * data;
    // size of the record
    uint64_t size;
    // key offset of record
    uint32_t keyOffset;
    // created record
    void * record;
    // record constructor
    Record(uint64_t sizeFromUser,  uint32_t keyOffsetFromUser);
    Record();

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

    /**
     * Compares two records' keys together
     * @param other is the other record to compare keys to the class' record
     * @return 1 if the class key is greater; -1 if the other key is greater
     */
     int compareTo(Record other);

     /**
      * Sets the compareCount variable back to 0
      */
     void resetCompareCount();

     /**
      * @return the compare count variable
      */
     long getCompareCount();

     void store(char * buffer, int offset);
     void storePartial(char * buffer, int offset, int start, int length);

private:
    // the total times the record has been compared to another record
    long compareCount;
    /**
    * This method will create a record in memory and fill it with random 64 bit integers
     * It is used to create the record during the initialization of the Record constructor
    * @return void* array as the created record
    */
    void* createRecord();
};


#endif //DB_RECORD_H
