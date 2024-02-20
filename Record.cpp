#include <iostream>
#include "rng.cpp"

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
* This method will compute a checksum on the record
*/
//TODO: complete this method



/**
  * This method compares two records' keys to see which one is greater
   * @param r1 is the first record for comparison
   * @param r2 is the second record for comparison
   * @returns 1 if r1's key > r2's key2, -1 if r1's key1 < r2's key2, or 0 if both keys are equal
  */
  //TODO: decide if we want to only allow keys to be integers as compare() is for strings
int compareRecordKeys(void* r1, void* r2, uint32_t keyOffset){
    // defines pointer to the first element in each record
    uint64_t* p1 = (uint64_t*) r1;
    uint64_t* p2 = (uint64_t*) r2;
    // obtains key location for each record
    uint64_t* key1Location = p1 + keyOffset;
    uint64_t* key2Location = p2 + keyOffset;
    // obtains key for each record
    uint64_t key1 = *key1Location;
    uint64_t key2 = *key2Location;
    // compares keys to return comparison value
    if (key1 > key2){
        return 1;
    } else if (key1 < key2){
        return -1;
    } else {
        return 0;
    }
}

int main(){
    // creates a record of size 100
    int size = 100;
    uint32_t keyOffset = 8;
    // calculates expected chunks
    int chunksInArray = ceil(size/keyOffset);
    uint64_t* recordPointer1 = (uint64_t*) createRecord(size);
    // prints out values in created record
    for (int i = 0; i <= chunksInArray; i++){
        std::cout << *(recordPointer1 + (i)) << ", ";
    }
    // displays comparison result for comparing records
    uint64_t* recordPointer2 = (uint64_t*) createRecord(size);
    int comparisonValue1 = compareRecordKeys(recordPointer1, recordPointer2, keyOffset);
    int comparisonValue2 = compareRecordKeys(recordPointer2, recordPointer1, keyOffset);
    std::cout << "\nfirst value " << comparisonValue1;
    std::cout << "\nsecond value " << comparisonValue2;
}