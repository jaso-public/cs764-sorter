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
    source = givenSource;
}

/**
* Returns a pointer to the next record in the list and checks that each record key is sorted
* @return pointer to next record or null if no more records exists
*/
Record *Witness::next() {

}

/**
  * Gets total number of generated records
  * @return the total number of record returned by next()
  */
long Witness::getCount() {

}

/**
  * Returns the checksum value of all the records
  * @return checksum value
  */
long Witness::getCrc() {

}

/**
 * Returns a true or false value indicating whether the records are sorted or not
 * @return true if records are sorted else false
 */
bool Witness::checkSorted() {

}