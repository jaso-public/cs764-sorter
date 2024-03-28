#include "StagedProviderTest.h"


StagedProviderTest::StagedProviderTest() {};

void StagedProviderTest::doTest(uint64_t size,  uint32_t keyOffset, long recordCount, int stagingLength, int bufferLength) {
    RandomGenerator rg(recordCount, size, keyOffset);
    Witness before(&rg);

    IODevice storage("storage.tmp");

    long storageOffset = 0;
    while(true) {
        Record* recPtr = before.next();
        if(!recPtr) break;
        Record rec = *recPtr;
        storage.write(storageOffset, rec.data, 0, sizeof(rec.data));
        storageOffset += sizeof(rec.data);
    }

    IODevice staging("staging.tmp");

    char * memory = new char[10*1024*1024]; // 10MB



    long storageStartOffset = 0; // we wrote the records at offset zero
    long stagingStartOffset = 12431; // some arbitrary place in the staging file

    char * buffer = memory;
    int bufferStartOffset = 20;

    char * transferBuffer = memory;
    int transferStartOffset = bufferStartOffset + bufferLength;
    int transferLength = stagingLength + bufferLength;

    StagingConfig stagingCfg;
    stagingCfg.recordSize = size;
    stagingCfg.recordCount = recordCount;
    stagingCfg.storage = storage;
    stagingCfg.storageStartOffset = storageStartOffset;
    stagingCfg.staging = staging;
    stagingCfg.stagingStartOffset = stagingStartOffset;
    stagingCfg.stagingLength = stagingLength;
    stagingCfg.buffer = buffer;
    stagingCfg.bufferStartOffset = bufferStartOffset;
    stagingCfg.bufferLength = bufferLength;
    stagingCfg.transferBuffer = transferBuffer;
    stagingCfg.transferStartOffset = transferStartOffset;
    stagingCfg.transferLength = transferLength;

    StagedProvider sp(stagingCfg);
    Witness after(&sp);
    Consumer c(&after);
    c.consume();

    assert(("The count of the before witness should have equaled the count of the after witness" && before.getCount() == after.getCount()));
    assert(("The checksum of the before witness should have equaled the checksum of the after witness" && before.getCrc() == after.getCrc()));

}

void StagedProviderTest::testSmall() {
    doTest(123, 8, 50,564,2048);
}

void StagedProviderTest::testMedium() {
    doTest(12003, 8, 50,1024,2048);
}

int main(){
    StagedProviderTest test;
    test.testSmall();
    test.testMedium();
}