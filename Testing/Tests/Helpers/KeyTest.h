#ifndef CS764_SORTER_KEYTEST_H
#define CS764_SORTER_KEYTEST_H
#include "Testing/SortingHelpers/Key.h"
#include <assert.h>


class KeyTest {
public:
    void testCompareWithNotEqualKeys();
    void testCompareWithEqualKeys();
    void testCompareWithSameKey();
};


#endif //CS764_SORTER_KEYTEST_H
