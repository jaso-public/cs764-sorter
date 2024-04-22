#pragma once

#include "Record.h"
#include "Provider.h"

/**
 * This class is utilized to verify the correctness of the sorting algorithm
 */
class Witness: public Provider {
public:
    /**
     * Class constructor
     * @param source a provider to obtain records from
     */
    Witness(shared_ptr<Provider> source): source(source), record(source->next()), count(0), checksum(0), sorted(true), duplicateCount(0) {}

    /**
     * Returns a pointer to the next record from the provider
     * Checks if the records are sorted and keeps track of duplicates
     * @return pointer to next record or a nullptr if no more records exists
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

    /**
     * Get method for the total number of records returned from the class' next() method
     * @return record count
     */
    uint64_t getCount() {
        return count;
    }

    /**
     * Returns the amount of duplicates uncovered
     * @return duplicate count
     */
    uint64_t getDuplicateCount() {
        return duplicateCount;
    }

   /**
    * Get method for the class' checksum value that is used to verify the sorting algorithm's correctness between witnesses
    * @return class' checksum value
    */
    uint64_t getChecksum() {
        return checksum;
    };

    /**
     * Get method to reveal if records were sorted or not
     * @return true if records were sorted else false
     */
    bool isSorted() {
        return sorted;
    }

     /**
      * Prints the class' statistics to the terminal
      * @param out is the stream to write the output to
      * @param name is a name to identify the Witness
      */
    void writeStats(std::ostream& out, string name) {
        out << "Witness: " << name << endl;
        out << "    record count     : " << count << endl;
        out << "    checksum         : " << checksum << endl;
        out << "    sorted           : " << (sorted ? "true" : "false") << endl;
        out << "    duplicate count  : " << duplicateCount << endl;
    }


private:
    shared_ptr<Provider> source; // the source that will generate records
    shared_ptr<Record> record;   // lastRecord seen
    uint64_t count;              // keeps track of all the records generate
    uint64_t checksum;           // keeps track of checksum value
    bool sorted;                 // bool value that indicates if records have been sorted
    uint64_t duplicateCount;     // total number of duplicates witness has seen
};
