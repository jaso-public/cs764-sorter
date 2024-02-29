#include "Provider.h"
#include "Record.h"
#include <iostream>


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
 * @returns the next record or a null record if the end of the list been reached
 */
Record Provider::next(){
    Record r(sizeOfRecords, keyOffset);
    if (numGenerated < numOfRecords){
        numGenerated++;
    } else {
        r.record = NULL;
    }
    return r;
}


//TODO: fix why this is not working
 int main(){
    Provider p(10,10,8);
}
