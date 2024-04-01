#include "ArrayProvider.h"


/**
 * Array provider constructor
 * @param givenName name to identify the given array iterator
 * @param givenRecords a vector of records
 */
ArrayProvider::ArrayProvider(std::string givenName, vector<Record> givenRecords) {
    // stores give variables as class variables
    this->name = givenName;
    this->records = givenRecords;
    // places pointer at start of records vector
    this->ptr = givenRecords.begin();

}

/**
 * Continues to return the next method while one exists
 * @return a pointer to the next record or a null pointer if the next record does not exist
 */
shared_ptr<Record> ArrayProvider::next() {
    // checks that another record exists
    if (ptr != records.end()){
        // create a pointer to the returned record
        Record result = *ptr;
        ptr++;
        shared_ptr<Record> recordPtr =  &result;
        return recordPtr;
    }
    return nullptr;
}
