#include <cassert>
#include <filesystem>
#include "src/Consumer.h"
#include "src/Generator.h"
#include "src/Witness.h"
#include "src/StorageProvider.h"
using namespace std;


void doTest(int recordSize, long recordCount, int stagingLength, int bufferLength, uint32_t keyOffset) {
    auto records = generateRandom(10);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness>  before = make_shared<Witness>(source);

    IODevice storage("../Files/storage.tmp");

    long storageOffset = 0;
    while(true) {
        shared_ptr<Record> recPtr = before->next();
        if(!recPtr) break;
        int recordSize = Record::getRecordSize();
        uint8_t *data = new uint8_t[recordSize];
        recPtr->store(data);
        storage.write(storageOffset, data, recordSize);
        delete(data);
        storageOffset += recordSize;

    }

    uint8_t* memory = new  uint8_t[10*1024*1024]; // 10MB


    long storageStartOffset = 0; // we wrote the records at offset zero

    uint8_t* buffer = memory;


    unique_ptr<StorageConfig> storageConfig = make_unique<StorageConfig>();
    storageConfig->buffer = buffer;
    storageConfig->startOffset = 20;
    shared_ptr<StorageProvider> sp =  make_shared<StorageProvider>(storageConfig);
    shared_ptr<Witness> after = make_shared<Witness>(sp);
    Consumer consumer(after);
    consumer.consume();

    assert(("The count of the before witness should have equaled the count of the after witness" && before->getCount() == after->getCount()));
    assert(("The checksum of the before witness should have equaled the checksum of the after witness" && before->getChecksum() == after->getChecksum()));

    remove("storage.tmp");
}

void testSmall() {
    doTest(123,50,564,2048, 8);
}

void testMedium() {
    doTest(123,50,564,2048, 8);
}

int main(){
    testSmall();
    testMedium();
}