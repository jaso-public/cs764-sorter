#ifndef CS764_SORTER_SORTERTEST_H
#define CS764_SORTER_SORTERTEST_H
#include "Testing/TestProviders/RandomGenerator.h"
#include "Testing/TestProviders/Printer.h"
#include "./Witness.h"
#include "./Config/SorterConfig.h"
#include "./Sort/Sorter.h"
#include "./Consumer.h"
#include <cassert>
#include <string>
using namespace std;


class SorterTest {
public:
    void testSmallSort();
    void testAllMemory();
    void testSpillToSsdFewBlocks();
    void testSpillToSsd();
    void testSpillToHdd();
    void testSpillToLotsOfHddRuns();
    void testZeroRecords();
};


#endif //CS764_SORTER_SORTERTEST_H
