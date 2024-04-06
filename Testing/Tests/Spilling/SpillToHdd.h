#ifndef CS764_SORTER_SPILLTOHDD_H
#define CS764_SORTER_SPILLTOHDD_H
#include "Config/SorterConfig.h"
#include "Providers/Provider.h"
#include "Witness.h"
#include "Sort/Sorter.h"
#include "Testing/TestProviders/Printer.h"
#include "Testing/TestProviders/Generators.h"
#include "Testing/TestProviders/ArrayProvider.h"
#include <string>
#include <cassert>
using namespace std;


class SpillToHdd {
public:
    void testSpillToHdd();
};


#endif //CS764_SORTER_SPILLTOHDD_H
