#ifndef CS764_SORTER_RANDOMGENERATOR_H
#define CS764_SORTER_RANDOMGENERATOR_H
#include "Providers/Provider.h"
#include <stdlib.h>

class RandomGenerator: public Provider{
public:
    long count;
    uint64_t size;
    uint32_t keyOffset;
    RandomGenerator(long count, uint64_t size, uint32_t keyOffset);
    shared_ptr<Record> next() override;
private:
    long generated;
};


#endif //CS764_SORTER_RANDOMGENERATOR_H
