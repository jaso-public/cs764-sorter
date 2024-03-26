#ifndef CS764_SORTER_STAGEDPROVIDERTEST_H
#define CS764_SORTER_STAGEDPROVIDERTEST_H
#include "Providers/StagedProvider.h"
#include "Consumer.h"
#include "Testing/TestProviders/RandomGenerator.h"
#include "Witness.h"
#include <cassert>


class StagedProviderTest {
public:
    void doTest(int recordSize, long recordCount, int stagingLength, int bufferLength);
    void testSmall();
    void testMedium();
    StagedProviderTest();
};


#endif //CS764_SORTER_STAGEDPROVIDERTEST_H
