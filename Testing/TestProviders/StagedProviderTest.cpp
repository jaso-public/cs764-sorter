#include "StagedProviderTest.h"
#include "RandomGenerator.h"
#include "Witness.h"
#include "IODevice.h"

void StagedProviderTest::doTest(int recordSize, long recordCount, int stagingLength, int bufferLength) {
    RandomGenerator rg(recordCount, recordSize);
    Witness before(rg);

    IODevice storage("storage.tmp");

    long storageOffset = 0;
    while(true) {
        Record* recPtr = before.next();
        if(!recPtr) break;
        Record rec = *recPtr;
        storage.write(storageOffset, sizeof(rec.data), 0, sizeof(rec.data));
        storageOffset += sizeof(rec.data);
    }

    IODevice staging("staging.tmp");

    byte[] memory = new byte[10*1024*1024]; // 10MB



    long storageStartOffset = 0; // we wrote the records at offset zero
    long stagingStartOffset = 12431; // some arbitrary place in the staging file

    byte[] buffer = memory;
    int bufferStartOffset = 20;

    byte[] transferBuffer = memory;
    int transferStartOffset = bufferStartOffset + bufferLength;
    int transferLength = stagingLength + bufferLength;


    StagedProvider.StagingConfig cfg = new StagedProvider.StagingConfig();
    cfg.recordSize = recordSize;
    cfg.recordCount = recordCount;
    cfg.storage = storage;
    cfg.storageStartOffset = storageStartOffset;
    cfg.staging = staging;
    cfg.stagingStartOffset = stagingStartOffset;
    cfg.stagingLength = stagingLength;
    cfg.buffer = buffer;
    cfg.bufferStartOffset = bufferStartOffset;
    cfg.bufferLength = bufferLength;
    cfg.transferBuffer = transferBuffer;
    cfg.transferStartOffset = transferStartOffset;
    cfg.transferLength = transferLength;

    StagedProvider sp = new StagedProvider(cfg);
    Witness after = new Witness(sp);
    Consumer c = new Consumer(after);
    c.consume();

    assertEquals(before.getCount(), after.getCount());
    assertEquals(before.getCrc(), after.getCrc());

}

void StagedProviderTest::testSmall() {
    doTest(123,50,564,2048);
}

void StagedProviderTest::testMedium() {
    doTest(12003,50,1024,2048);
}