#ifndef CS764_SORTER_MEMORYPROVIDER_H
#define CS764_SORTER_MEMORYPROVIDER_H
#include "Records/Record.h"
#include "Provider.h"
#include <limits.h>
#include <iostream>
#include "Config/SorterConfig.h"
#include <algorithm>
using namespace std;

/**
 * This class is used to create continuously create buffer space for a new record
 */
class MemoryProvider: public Provider {

public:
     MemoryProvider(uint8_t *buffer, uint32_t recordCount): buffer(buffer), recordCount(recordCount), generatedRecordCount(0) {}

     shared_ptr<Record> next() override {
        if(generatedRecordCount >= recordCount) return nullptr;

        uint8_t *startOfRecord = buffer + generatedRecordCount * Record::getRecordSize();
        generatedRecordCount++;
        return make_shared<Record>(startOfRecord);
    }

private:
    uint8_t *buffer; // the buffer holding the record data
    uint64_t generatedRecordCount;
    uint64_t recordCount;
};


#endif //CS764_SORTER_MEMORYPROVIDER_H
