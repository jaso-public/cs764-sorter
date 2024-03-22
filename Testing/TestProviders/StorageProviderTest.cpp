#include "StorageProviderTest.h"
#include "RandomGenerator.h"
#include "Witness.h"

void StorageProviderTest::doTest(int recordSize, long recordCount, int stagingLength, int bufferLength) {

    RandomGenerator rg(recordCount, recordSize);
    Witness before(rg);

    //TODO: here
    File storageFile = File.createTempFile("storage", ".tmp");
    storageFile.deleteOnExit();
    IoDevice storage = new IoDevice(storageFile);

    long storageOffset = 0;
    while(true) {
        Record rec = before.next();
        if(rec==null) break;
        storage.write(storageOffset, rec.data, 0, rec.data.length);
        storageOffset += rec.data.length;
    }

    byte[] memory = new byte[10*1024*1024]; // 10MB


    long storageStartOffset = 0; // we wrote the records at offset zero

    byte[] buffer = memory;
    int bufferStartOffset = 20;


    StorageProvider sp = new StorageProvider(
            recordSize,
            recordCount,
            storage,
            storageStartOffset,
            buffer,
            bufferStartOffset,
            bufferLength);


    Witness after = new Witness(sp);
    Consumer c = new Consumer(after);
    c.consume();

    assertEquals(before.getCount(), after.getCount());
    assertEquals(before.getCrc(), after.getCrc());
}
