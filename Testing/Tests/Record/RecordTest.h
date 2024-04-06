#ifndef CS764_SORTER_RECORDTEST_H
#define CS764_SORTER_RECORDTEST_H
#include <iostream>
#include "Records/Record.h"
#include "Records/GenerateRecords.h"
#include <assert.h>

using namespace std;


class RecordTest {
public:
    void testNoParameterConstructor();
    void testDataParameterConstructor();
    void testIsDuplicate();
    void testCompare();
    void testCheckSum();
};


#endif //CS764_SORTER_RECORDTEST_H
