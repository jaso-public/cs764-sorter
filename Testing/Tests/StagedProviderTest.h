#ifndef CS764_SORTER_STAGEDPROVIDERTEST_H
#define CS764_SORTER_STAGEDPROVIDERTEST_H


class StagedProviderTest {
public:
    void doTest(int recordSize, long recordCount, int stagingLength, int bufferLength);
    void testSmall();
    void testMedium();
    StagedProviderTest();
};


#endif //CS764_SORTER_STAGEDPROVIDERTEST_H
