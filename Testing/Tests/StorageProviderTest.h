#ifndef CS764_SORTER_STORAGEPROVIDERTEST_H
#define CS764_SORTER_STORAGEPROVIDERTEST_H
#include "Testing/TestProviders/RandomGenerator.h"
#include "Witness.h"
#include "Consumer.h"
#include <cassert>
#include <filesystem>
#include "Providers/StorageProvider.h"
using namespace std;


class StorageProviderTest {
public:
    static void doTest(int recordSize, long recordCount, int stagingLength, int bufferLength);
    void testSmall();
    void testMedium();
    StorageProviderTest();
};


#endif //CS764_SORTER_STORAGEPROVIDERTEST_H
