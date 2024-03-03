#ifndef DB_WITNESS_H
#define DB_WITNESS_H
#include "Provider.h"

/**
 * This class will be utilized to verify the correctness of the records sorting algorithm
 * Implements the Provider class
 */
class Witness:Provider{
public:
    // the source that will generate records
    Provider source;

    // the witness constructor that takes in a provider
    Witness(Provider givenSource);

    /**
   * Returns a pointer to the next record in the list and checks that each record key is sorted
   * @return pointer to next record or null if no more records exists
   */
    Record* next();

    /**
     * Gets total number of generated records
     * @return the total number of record returned by next()
     */
    long getCount();

    /**
     * Returns the checksum value of all the records
     * @return checksum value
     */
    long getCrc();

    /**
   * Returns a true or false value indicating whether the records are sorted or not
   * @return true if records are sorted else false
   */
    bool checkSorted();

private:
    // keeps track of all the records generated
    long count;
    // keeps track of checksum value
    long crc;
    // pointer to the key of the last record generated
    uint64_t* lastKeyPtr;
    // bool value that indicates if records have been sorted
    bool isSorted;
};


#endif //DB_WITNESS_H
