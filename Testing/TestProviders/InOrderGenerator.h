#ifndef CS764_SORTER_INORDERGENERATOR_H
#define CS764_SORTER_INORDERGENERATOR_H
#include "./Providers/Provider.h"
#include <stdlib.h>

/**
 * This class can be used to generate records of a certain size and amount
 */
class InOrderGenerator:public Provider {
public:
    // represents total number of records to generate
    long count;
    // represents the size of the records
    uint64_t size;
    uint32_t keyOffset;
    // class constructor
    InOrderGenerator(long count, uint64_t size,  uint32_t keyOffset);
    // returns a pointer to the next record or a null pointer if a next record does not exist
    Record* next() override;
private:
    // stores actual number of records currently generated
    long generated;
};


#endif //CS764_SORTER_INORDERGENERATOR_H
