#pragma once

#include "Record.h"
#include "Provider.h"

/**
 * This class enables defining and returning a given record
 */
class SingleProvider: public Provider {
public:
    SingleProvider(): record(nullptr) {}

    /**
     * Sets the class record's variable to the given record
     * @param r the new record variable of the class
     */
    void reset(shared_ptr<Record> r) {
        record = r;
    }

    // returns the class record's variable and then turns it to null
    shared_ptr<Record> next() override {
        shared_ptr<Record> result = record;
        record = nullptr;
        return result;
    }

private:
    shared_ptr<Record> record; // a pointer to a record or a null pointer if the record does not exist
 };

