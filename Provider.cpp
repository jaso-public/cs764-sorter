#include "Provider.h"
#include "Record.h"

/**
 * Initializes provider constructor
 * @param numOfRecordsFromUser number of records needing to be generated
 * @param sizeOfRecordsFromUser size of each individual record
 * @param keyOffsetFromUser key offset value
 */
Provider::Provider(uint64_t numOfRecordsFromUser, uint64_t sizeOfRecordsFromUser, uint32_t keyOffsetFromUser) {
    numOfRecords = numOfRecordsFromUser;
    sizeOfRecords = sizeOfRecordsFromUser;
    keyOffset = keyOffsetFromUser;
    // starts as 0 since none have been generated yet
    numGenerated = 0;
}

/**
 * Generates the next record
 * @return a pointer to the next record or null if all records have been generated
 */
Record* Provider::next(){
    if (numGenerated < numOfRecords){
        numGenerated++;
        return new Record(sizeOfRecords, keyOffset);
    }
    return nullptr;
}
