#include "Witness.h"
#include "Provider.h"
#include "Record.h"
using namespace std;
#include <iostream>

/**
 * Initializes witness constructor
 * @param givenSource the source to get records from
 */
Witness::Witness(Provider givenSource) {
    count = 0;
    crc = 0;
    lastKeyPtr = nullptr;
    isSorted = true;
    source = givenSource;
}

/**
* Returns a pointer to the next record in the list and checks that each record key is sorted
* @return pointer to next record or null if no more records exists
*/
Record *Witness::next() {
    // gets the next record pointer and returns the pointer if it is null
    Record* recordPtr = source.next();
    if (!recordPtr) return recordPtr;
    // else obtains the record and checks if it is sorted
    Record record = *recordPtr;
    if (isSorted){
        uint64_t key = record.getRecordKey();
        if (lastKeyPtr){
            // gets the last key value
            uint64_t lastKey = *lastKeyPtr;
            if (lastKey>key) isSorted = false;
        }
        // sets pointer to most recently obtained key
        lastKeyPtr = &key;
    }
    // increases count and computes the sequential check sum value
    count++;
    crc ^= record.completeChecksumCheck();
    return recordPtr;
}

/**
  * Gets total number of generated records
  * @return the total number of record returned by next()
  */
long Witness::getCount() {
    return count;
}

/**
  * Returns the checksum value of all the records
  * @return checksum value
  */
long Witness::getCrc() {
    return crc;
}

/**
 * Returns a true or false value indicating whether the records are sorted or not
 * @return true if records are sorted else false
 */
bool Witness::checkSorted() {
    return isSorted;
}

// main method to check that witness is working
int main(){
    //create a provider to generate 10 records
    Provider p(10,10,8);
    // test witness methods
    Witness w(p);
    bool sorted = w.checkSorted();
    long crc = w.getCrc();
    long count = w.getCount();
    cout << "Should be false: " << sorted << "\n";
    cout << "Should be 0: " << crc << "\n";
    cout << "Should be 0: "<< count << "\n";
    for (int i = 0; i < 11; i++){
        Record* ptr = w.next();
        if (!ptr){
            cout << "Null pointer was reached" << "\n";
        } else{
            Record r = *ptr;
            cout << r.record << "\n";
        }
    }
    sorted = w.checkSorted();
    crc = w.getCrc();
    count = w.getCount();
    cout << "Should be false: " << sorted << "\n";
    cout << "Should not be 0: " << crc << "\n";
    cout << "Should be 10: "<< count << "\n";
}