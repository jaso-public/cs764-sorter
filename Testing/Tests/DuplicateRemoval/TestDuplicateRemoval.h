#ifndef CS764_SORTER_TESTDUPLICATEREMOVAL_H
#define CS764_SORTER_TESTDUPLICATEREMOVAL_H
#include <cassert>
using namespace std;


class TestDuplicateRemoval {
public:
    // normal case
    void testRemovingDuplicates1();
    // see what happens when there are no duplicates
    void testRemovingNoDuplicates2();
    // see what happens when there are all duplicates
    void testRemovingAllDuplicates3();
    // see what happens when the given file is empty
    void testEmptyInputFile4();
};


#endif //CS764_SORTER_TESTDUPLICATEREMOVAL_H
