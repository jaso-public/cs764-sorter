#ifndef CS764_SORTER_LOTSOFHDDRUNS_H
#define CS764_SORTER_LOTSOFHDDRUNS_H
#include "../../Config/SorterConfig.h"
#include "../../Sort/Sorter.h"
#include "../../Witness.h"
#include "../../Consumer.h"
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
