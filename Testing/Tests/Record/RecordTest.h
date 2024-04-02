#ifndef CS764_SORTER_RECORDTEST_H
#define CS764_SORTER_RECORDTEST_H
#include <iostream>
#include "Records/Record.h"
#include "Config/SorterConfig.h"
#include "Records/GenerateRecords.h"
using namespace std;


class RecordTest {
public:
    void testNoParameterConstructor();
    void testDataParameterConstructor();
    void testCompareRecords();
};


#endif //CS764_SORTER_RECORDTEST_H
