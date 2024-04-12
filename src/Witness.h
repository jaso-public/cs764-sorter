#pragma once

#include "Record.h"
#include "Provider.h"

/**
 * This class will be utilized to verify the correctness of the records sorting algorithm
 * Implements the Provider class
 */
class Witness: public Provider {
public:
    // the witness constructor that takes in a provider
    Witness(shared_ptr<Provider> source): source(source), record(source->next()), count(0), checksum(0), sorted(true) {}

    /**
     * Returns a pointer to the next record in the list and checks that each record key is sorted
     * @return pointer to next record or null if no more records exists
     */
    shared_ptr<Record> next() override {
        if(record == nullptr) return nullptr;

        shared_ptr<Record> result = record;
        count++;
        checksum ^= result->checksum();

        record = source->next();
        if(record == nullptr) return result;

        int cmp = result->compareTo(record);
        if(cmp == 0) duplicateCount++;
        if(cmp > 0) sorted = false;
        return result;
    }

    uint64_t getCount() {
        return count;
    }

    uint64_t getDuplicateCount() {
        return duplicateCount;
    }
    uint64_t getChecksum() {
        return checksum;
    };

    bool isSorted() {
        return sorted;
    }

private:
    shared_ptr<Provider> source; // the source that will generate records
    shared_ptr<Record> record;   // lastRecord seen
    uint64_t count;              // keeps track of all the records generated
    uint64_t checksum;           // keeps track of checksum value
    bool sorted;                 // bool value that indicates if records have been sorted
    uint64_t duplicateCount;     // bool value if the witness saw two consecutive identical records
};
