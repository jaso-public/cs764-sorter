#ifndef CS764_SORTER_LOTSOFHDDRUNS_H
#define CS764_SORTER_LOTSOFHDDRUNS_H
#include "../../Config/SorterConfig.h"
#include "../../src/Sorter.h"
#include "../../src/Witness.h"
#include "../../test/helpers/Consumer.h"
#include "Testing/TestProviders/Generators.h"
#include "Testing/TestProviders/ArrayProvider.h"
#include <cassert>
#include <string>
using namespace std;


class LotsOfHddRuns {
public:
    void testSpillToLotsOfHddRuns();
};


#endif //CS764_SORTER_LOTSOFHDDRUNS_H
