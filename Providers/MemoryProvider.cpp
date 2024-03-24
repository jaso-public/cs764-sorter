#include "MemoryProvider.h"
#include <limits.h>
#include <iostream>
using namespace std;
/**
 * Class constructor that assigns given variables to class variables
 * @param givenBuffer buffer of memory
 * @param givenOffset offset of record
 * @param givenRecordCount total number of records to create
 * @param givenRecordSize number of records already created
 */
MemoryProvider::MemoryProvider(char * buffer, long offset, long recordCount, int recordSize, uint32_t keyOffset) {
    this->buffer = buffer;
    this->offset = safeIntCast(offset);
    this->recordCount = safeIntCast(recordCount);
    this->recordSize = recordSize;
    this->keyOffset = keyOffset;
}

/**
  * Creates another buffer of memory for the new record and assigns a record to it
  * @return pointer to the next created record or a null pointer if recordCount has been reached
  */
Record* MemoryProvider::next() {
    // if all records and memory spaces have been created
    if(nextRecord >= recordCount) return nullptr;
    nextRecord++;
    Record r(recordSize, keyOffset);
    Record* ptr = &r;
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

int main(){};