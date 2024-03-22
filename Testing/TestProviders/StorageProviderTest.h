#ifndef CS764_SORTER_STORAGEPROVIDERTEST_H
#define CS764_SORTER_STORAGEPROVIDERTEST_H


class StorageProviderTest {
public:
    void doTest(int recordSize, long recordCount, int stagingLength, int bufferLength);
    void testSmall();
    void testMedium();
};


#endif //CS764_SORTER_STORAGEPROVIDERTEST_H
