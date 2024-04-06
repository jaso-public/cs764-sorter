#ifndef CS764_SORTER_SPILLONEBLOCKTOSSD_H
#define CS764_SORTER_SPILLONEBLOCKTOSSD_H
#include "Testing/TestProviders/Generators.h"
#include "Testing/TestProviders/ArrayProvider.h"
#include "Witness.h"
#include "Config/SorterConfig.h"
#include "Sort/Sorter.h"
#include "Consumer.h"
#include <cassert>
#include <string>
using namespace std;


class SpillOneBlockToSsd {
public:
    void testSpillToSsdFewBlocks();
    SpillOneBlockToSsd();
};


#endif //CS764_SORTER_SPILLONEBLOCKTOSSD_H
