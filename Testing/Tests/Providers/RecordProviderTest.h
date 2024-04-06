#ifndef CS764_SORTER_RECORDPROVIDERTEST_H
#define CS764_SORTER_RECORDPROVIDERTEST_H
#include <assert.h>
#include "Providers/RecordProvider.h"
#include "Providers/Provider.h"
#include "Witness.h"
#include "Testing/SortingHelpers/NoopSorter.h"
#include "Consumer.h"
#include "Testing/TestProviders/DropFirst.h"
#include "./Testing/SortingHelpers/TreeSorter.h"
#include <cassert>
#include <string>
#include "Testing/TestProviders/Printer.h"
#include "Providers/Dedooper.h"


class RecordProviderTest {
public:
    void testNext();
    void testInputRecord();
    void testTenInOrder();
    void testDropOne();
    void testTreeSorter();

};


#endif //CS764_SORTER_RECORDPROVIDERTEST_H
