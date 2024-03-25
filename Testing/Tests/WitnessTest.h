#ifndef CS764_SORTER_WITNESSTEST_H
#define CS764_SORTER_WITNESSTEST_H
#include "Providers/Provider.h"
#include "Testing/TestProviders/InOrderGenerator.h"
#include "Witness.h"
#include "Testing/SortingHelpers/NoopSorter.h"
#include "Consumer.h"
#include "Testing/TestProviders/DropFirst.h"
#include "./Testing/SortingHelpers/TreeSorter.h"
#include <cassert>
#include <string>
#include "Testing/TestProviders/Printer.h"
#include "Testing/TestProviders/RandomGenerator.h"
using namespace std;


class WitnessTest {
public:
    void testTenInorder();
    void testDropOne();
    void testRandomOrder();
    void testTreeSorter();
    void testRandomOrderWithPrinting();
    void testTreeSorterWithPrinting();
    WitnessTest();
};


#endif //CS764_SORTER_WITNESSTEST_H
