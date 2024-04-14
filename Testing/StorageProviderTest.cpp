#include <cassert>
#include <filesystem>
#include "src/Consumer.h"
#include "src/Witness.h"
#include "src/StorageProvider.h"
using namespace std;


void doTest(long recordCount) {
    auto source = make_shared<RandomProvider>(recordCount);
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

    uint8_t* buffer = memory;

    unique_ptr<StorageConfig> storageConfig = make_unique<StorageConfig>();
    storageConfig->buffer = buffer;
    storageConfig->startOffset = 20;
    shared_ptr<StorageProvider> sp =  make_shared<StorageProvider>(storageConfig);
    shared_ptr<Witness> after = make_shared<Witness>(sp);
    auto consumer = make_shared<NoopConsumer>(after);
    consumer->consume();

    assert(("The count of the before witness should have equaled the count of the after witness" && before->getCount() == after->getCount()));
    assert(("The checksum of the before witness should have equaled the checksum of the after witness" && before->getChecksum() == after->getChecksum()));

    remove("storage.tmp");
}

int main(){
    doTest(10);
    doTest(50);
}