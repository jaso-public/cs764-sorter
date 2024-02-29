#include "rng.cpp"
#include "Record.h"
using namespace std;

/**
 * Initializes record constructor
 * @param sizeFromUser size of record
 * @param keyOffsetFromUser key offset of record
 */
Record::Record(int sizeFromUser, uint32_t keyOffsetFromUser) {
    size = sizeFromUser;
    keyOffset = keyOffsetFromUser;
    // created record
    record = createRecord();
}

/**
 * This method will create a record in memory and fill it with random 64 bit integers
 * @return void* array as the created record
 */
void* Record::createRecord(){
    void* record = malloc(size);
    fill(size, record);
    return record;
}

/**
 * This method obtains the key from a given record
 * @return record's key
 */
uint64_t Record::getRecordKey(){
    uint64_t* p = (uint64_t*) record;
    uint64_t* keyLocation = p + keyOffset;
    uint64_t key = *keyLocation;
    return key;
}

/**
 * This method will compute the checksum value of a given record
 * @returns the checksum value of the record
 */
bool Record::completeChecksumCheck(){
    int extra = size & 7;
    int num = size >> 3;

    uint64_t result = 0;
    uint64_t *a = (uint64_t*) record;
    for(int i=0; i<num ; i++){
        result = result ^ a[i];
    }

    if(extra) {
        uint64_t tmp = 0;
        void* ending = a + num;
        memcpy(&tmp, ending, extra);
        result ^= tmp;
    }

    return result;
}


///**
// * main method created for testing purposes
// */
//
//int main(){
//    // creates a record of size 100
//    int size = 100;
//    uint32_t keyOffset = 8;
//    // calculates expected chunks
//    int chunksInArray = ceil(size/keyOffset);
//    uint64_t* recordPointer1 = (uint64_t*) createRecord(size);
//    //prints out values in created record
//    cout << "here is the created record: ";
//    for (int i = 0; i <= chunksInArray; i++){
//        cout << *(recordPointer1 + (i)) << ", ";
//    }
//    // prints out result of checksum
//    cout << "\n here is the record after the checksum: " << getXORChecksum(size, recordPointer1);
//}
