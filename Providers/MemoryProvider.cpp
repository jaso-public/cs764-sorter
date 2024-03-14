#include "MemoryProvider.h"

/**
 * Class constructor that assigns given variables to class variables
 * @param givenBuffer buffer of memory
 * @param givenOffset offset of record
 * @param givenRecordCount total number of records to create
 * @param givenRecordSize number of records already created
 */
MemoryProvider::MemoryProvider(char *givenBuffer, long givenOffset, long givenRecordCount, int givenRecordSize) {
    this->buffer = givenBuffer;
    this->offset = safeIntCast(givenOffset);
    this->recordCount = safeIntCast(givenRecordCount);
    this->recordSize = givenRecordSize;
}

/**
  * Creates another buffer of memory for the new record and assigns a record to it
  * @return pointer to the next created record or a null pointer if recordCount has been reached
  */
Record* MemoryProvider::next() {
    // if all records and memory spaces have been created
    if(nextRecord >= recordCount) return nullptr;
    // creates a byte array of size record size
    char data[recordSize];
    nextRecord++;
}
