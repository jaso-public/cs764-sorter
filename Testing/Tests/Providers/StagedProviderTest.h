#ifndef CS764_SORTER_STAGEDPROVIDERTEST_H
#define CS764_SORTER_STAGEDPROVIDERTEST_H
#include "Providers/StagedProvider.h"
#include "Consumer.h"
#include "Testing/TestProviders/Generators.h"
#include "Testing/TestProviders/ArrayProvider.h"
#include "Config/SorterConfig.h"
#include "Witness.h"
#include <cassert>


class StagedProviderTest {
public:
    void doTest(uint64_t size,  uint32_t keyOffset, long recordCount, int stagingLength, int bufferLength);
    void testSmall();
    void testMedium();
    StagedProviderTest();
};


#endif //CS764_SORTER_STAGEDPROVIDERTEST_H
