#ifndef DB_PROVIDER_H
#define DB_PROVIDER_H
#include <stdint.h>
#include "Record.h"

/**
 * This is the provider class that will generate all the desired records
 */
class Provider {
private:
        // the key offset of a record
        uint32_t keyOffset;
        // stores the total number of records generated by provider
        uint64_t numGenerated;
        // stores the number of records to generate as given by the user
        uint64_t numOfRecords;
        // stores the size of the records as given by user
        uint64_t sizeOfRecords;

public:
    // default constructor
    Provider();
    // Provider constructor
    Provider(uint64_t numOfRecordsFromUser, uint64_t sizeOfRecordsFromUser, uint32_t keyOffsetFromUser);
    // returns the next record
    Record next();
};


#endif //DB_PROVIDER_H
