#include "StorageProviderTest.h"


StorageProviderTest::StorageProviderTest() {};

void StorageProviderTest::doTest(int recordSize, long recordCount, int stagingLength, int bufferLength, uint32_t keyOffset) {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordSize = recordSize;
    cfg->recordCount = recordCount;
    cfg->keyOffset = keyOffset;
    RandomGenerator rg(*cfg);
    Witness before(&rg);

    IODevice storage("../Files/storage.tmp");

    long storageOffset = 0;
    while(true) {
        shared_ptr<Record> recPtr = before.next();
        if(!recPtr) break;
        Record rec = *recPtr;
        storage.write(storageOffset, rec.data, 0, sizeof(rec.data));
        storageOffset += sizeof(rec.data);
    }

    uint8_t* memory = new  uint8_t[10*1024*1024]; // 10MB


    long storageStartOffset = 0; // we wrote the records at offset zero

    uint8_t* buffer = memory;
    int bufferStartOffset = 20;

    StorageProvider sp(storage,storageStartOffset,buffer,bufferStartOffset,bufferLength, *cfg);


    Witness after(&sp);
    Consumer c(&after);
    c.consume();

    assert(("The count of the before witness should have equaled the count of the after witness" && before.getCount() == after.getCount()));
    assert(("The checksum of the before witness should have equaled the checksum of the after witness" && before.getCrc() == after.getCrc()));

    remove("storage.tmp");
}

void StorageProviderTest::testSmall() {
    doTest(123,50,564,2048, 8);
}

void StorageProviderTest::testMedium() {
    doTest(123,50,564,2048, 8);
}

int main(){
    StorageProviderTest test;
    test.testSmall();
//    test.testMedium();
}