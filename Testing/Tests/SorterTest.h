#ifndef CS764_SORTER_SORTERTEST_H
#define CS764_SORTER_SORTERTEST_H


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
