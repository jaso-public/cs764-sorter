#include "Witness.h"
#include "Providers/Provider.h"
/**
 * Initializes witness constructor and sets all values to their defaults
 * @param givenSource the source to get records from
 */
Witness::Witness(Provider* givenSource) {
    this->count = 0;
    this->crc = 0;
    this->lastKeyPtr = nullptr;
    this->isSorted = true;
    this->source = givenSource;
}

/**
* Returns a pointer to the next record in the list and checks that each record key is sorted
* @return pointer to next record or a null pointer if no more records exists
*/

Record* Witness::next() {
    // gets the next record pointer and returns the pointer if it is null
    Record* recordPtr = source->next();
    if (!recordPtr) return nullptr;
    // else obtains the record and checks if it is sorted
    Record record = *recordPtr;
    if (isSorted){
        uint64_t key = record.getRecordKey();
        if (lastKeyPtr){
            // gets the last key value
            uint64_t lastKey = *lastKeyPtr;
            // sorting in ascending order
            if (lastKey>key) isSorted = false;
        }
        // sets pointer to point to recently obtained key
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