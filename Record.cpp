#include <iostream>
#include "rng.cpp"
using namespace std;

/**
 * This method will create a record in memory and fill it with random 64 bit integers
 * @param size the size of the record
 * @return void* array as the created record
 */
void* createRecord(int size){
    void* record = malloc(size);
    fill(size, record);
    return record;
}

/**
 * This method obtains the key from a given record
 * @param record the record to get the key from
 * @param keyOffset the offset value used to find the key location
 * @return record's key
 */
uint64_t getRecordKey(void* record, uint32_t keyOffset){
    uint64_t* p = (uint64_t*) record;
    uint64_t* keyLocation = p + keyOffset;
    uint64_t key = *keyLocation;
    return key;
}

/**
 * This method will compute the checksum value of a given record
 * @param size the size of the record
 * @param record the record
 * @returns the checksum value of the record
 */
uint64_t getXORChecksum(int size, void* record) {
    int extra = size & 7;
    int num = size >> 3;

    uint64_t result = 0;
    uint64_t *a = (uint64_t*) record;
    for(int i=0; i<num ; i++){
        result ^= a[i];
    }

    if(extra) {
        uint64_t tmp = 0;
        void* ending = a + num;
        memcpy(&tmp, ending, extra);
        result ^= tmp;
    }

    return result;
}

/**
 * main method created for testing purposes
 */

int main(){
    // creates a record of size 100
    int size = 100;
    uint32_t keyOffset = 8;
    // calculates expected chunks
    int chunksInArray = ceil(size/keyOffset);
    uint64_t* recordPointer1 = (uint64_t*) createRecord(size);
    //prints out values in created record
    cout << "here is the created record: ";
    for (int i = 0; i <= chunksInArray; i++){
        cout << *(recordPointer1 + (i)) << ", ";
    }
    // prints out result of checksum
    //TODO: pretty sure this value is not correct, need to test
    cout << "\n here is the record after the checksum: " << getXORChecksum(size, recordPointer1);
}
