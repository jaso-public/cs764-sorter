#ifndef CS764_SORTER_RANDOMGENERATOR_H
#define CS764_SORTER_RANDOMGENERATOR_H
#include "Provider.h"
#include <stdlib.h>

class RandomGenerator: public Provider{
public:
    long count;
    int size;
    RandomGenerator(long count, int size);
    Record* next();
private:
    long generated = 0;
    int rng = rand();
};


#endif //CS764_SORTER_RANDOMGENERATOR_H
