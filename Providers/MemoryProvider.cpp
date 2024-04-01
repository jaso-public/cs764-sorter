#include "MemoryProvider.h"

/**
 * Class constructor that assigns given variables to class variables
 * @param givenBuffer buffer of memory
 * @param givenOffset offset of record
 * @param givenRecordCount total number of records to create
 * @param givenRecordSize number of records already created
 */
MemoryProvider::MemoryProvider(uint8_t *buffer, long offset, long recordCount, int recordSize, uint32_t keyOffset, uint32_t keySize) {
    this->buffer = *buffer;
    this->offset = safeIntCast(offset);
    this->recordCount = safeIntCast(recordCount);
    this->recordSize = recordSize;
    this->keyOffset = keyOffset;
    this->keySize = keySize;
}

/**
  * Creates another buffer of memory for the new record and assigns a record to it
  * @return pointer to the next created record or a null pointer if recordCount has been reached
  */
shared_ptr<Record> MemoryProvider::next() {
    // if all records and memory spaces have been created
    if(nextRecord >= recordCount) return nullptr;
    nextRecord++;
    Record::staticInitialize(recordSize, keyOffset, keySize);
    shared_ptr<Record> ptr(new Record);
    return ptr;
}

int MemoryProvider::safeIntCast(long value) {
    try{
        if(value>INT_MAX) throw (value);
    } catch (long failedResult){
        cout << "Conversion from long to int failed; long was too large\n";
    }
    return  static_cast<int> (value);
}
