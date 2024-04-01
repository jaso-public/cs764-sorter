#ifndef CS764_SORTER_RANDOMGENERATOR_H
#define CS764_SORTER_RANDOMGENERATOR_H
#include "Providers/Provider.h"
#include <stdlib.h>
#include "Config/SorterConfig.h"

class RandomGenerator: public Provider{
public:
    RandomGenerator(SorterConfig cfg);
    shared_ptr<Record> next() override;
private:
    long generated;
    SorterConfig cfg;
};


#endif //CS764_SORTER_RANDOMGENERATOR_H
