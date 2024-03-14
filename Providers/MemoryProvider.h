#ifndef CS764_SORTER_MEMORYPROVIDER_H
#define CS764_SORTER_MEMORYPROVIDER_H
#include "Records/Record.h"

/**
 * This class is used to create continuously create buffer space for a new record
 */
class MemoryProvider {
private:
    // buffer of memory
    char * buffer;
    // offset record
    int offset;
    //  total number of records (memory spaces) to be returned/created
    int recordCount;
    // the size of each record
    int recordSize;
    //  total number of records returned so far
    int nextRecord;
    /**
     * Converts a long value to an integer if it is a valid conversion
     * @param the long value wanted to be converted
     * @return an integer if the conversion could occur
     * @throws an exception
     */
    int safeIntCast(long value);

public:
    /**
     * Class constructor that assigns given variables to class variables
     * @param givenBuffer buffer of memory
     * @param givenOffset offset of record
     * @param givenRecordCount total number of records to create
     * @param givenRecordSize number of records already created
     */
    MemoryProvider(char *givenBuffer, long givenOffset, long givenRecordCount, int givenRecordSize);

    /**
     * Creates another buffer of memory for the new record and assigns a record to it
     * @return pointer to the next created record or a null pointer if recordCount has been reached
     */
    Record* next();
};


#endif //CS764_SORTER_MEMORYPROVIDER_H
