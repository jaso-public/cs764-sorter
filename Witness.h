#ifndef CS764_SORTER_WITNESS_H
#define CS764_SORTER_WITNESS_H
#include "Providers/Provider.h"
#include "Records/Record.h"

#include <memory>
using namespace std;

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
        if(record != nullptr && sorted) sorted = result->compareTo(record);

        return result;
    }

    long getCount() {
        return count;
    }

    uint64_t getChecksum() {
        return checksum;
    };

    bool isSorted() {
        return sorted;
    }

private:
    shared_ptr<Provider> source; // the source that will generate records
    shared_ptr<Record> record; // lastRecord seen

    uint64_t count; // keeps track of all the records generated
    uint64_t checksum; // keeps track of checksum value
    bool sorted; // bool value that indicates if records have been sorted
};

#endif //CS764_SORTER_WITNESS_H
