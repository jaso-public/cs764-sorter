#include "Provider.h"
using namespace std;

Provider::Provider() {}
/**
 * Initializes provider constructor
 * @param numOfRecordsFromUser number of records needing to be generated
 * @param sizeOfRecordsFromUser size of each individual record
 * @param keyOffsetFromUser key offset value
 */
Provider::Provider(uint64_t numOfRecordsFromUser, uint64_t sizeOfRecordsFromUser, uint32_t keyOffsetFromUser) {
    this->numOfRecords = numOfRecordsFromUser;
    this->sizeOfRecords = sizeOfRecordsFromUser;
    this->keyOffset = keyOffsetFromUser;
    // starts as 0 since none have been generated yet
    this->numGenerated = 0;
}

/**
 * Generates the next record
 * @returns the a pointer to the next record or a null pointer record if the end of the list been reached
 */
Record* Provider::next(){
    if (numGenerated < numOfRecords){
        numGenerated++;
        Record r(sizeOfRecords, keyOffset);
        Record* ptr = &r;
        return nullptr;
    }
    return nullptr;
}

 int main(){
    // create a provider to generate 10 records
    Provider p(10,10,8);
    // checks that all 10 records are generated then null pointer is reached
    for (int i = 0; i < 11; i++){
        Record* ptr = p.next();
        if (!ptr){
           // cout << "Null pointer was reached";
        } else{
            Record r = *ptr;
           // cout << r.record << "\n";
        }
    }
}


