#include <cassert>
#include <memory>

#include "Record.h"
#include "Provider.h"
#include "Witness.h"
#include "StagedProvider.h"

#include "src/Consumer.h"
#include "src/Generator.h"


void doTest(uint64_t size,  uint32_t keyOffset, long recordCount, int stagingLength, int bufferLength) {

    auto records = generateRandom(recordCount);
    shared_ptr<Provider> provider = make_shared<ArrayProvider>("name", records);
    auto before = make_shared<Witness>(provider);

    int recordSize = Record::getRecordSize();
    uint8_t buffer[recordSize];
    uint8_t *bufferPtr = &buffer[0];

    auto storage = make_shared<IODevice>("../Files/storage.tmp");

    long storageOffset = 0;
    while(true) {
        shared_ptr<Record> recPtr = before->next();
        if(!recPtr) break;
        recPtr->store(bufferPtr);
        storage->write(storageOffset, bufferPtr, recordSize);
        storageOffset += recordSize;
    }

    auto staging = make_shared<IODevice>("../Files/staging.tmp");

    uint8_t memory[1024*1024]; // 10MB
    uint8_t* memoryPtr = &memory[0];

    long storageStartOffset = 0; // we wrote the records at offset zero
    long stagingStartOffset = 12431; // some arbitrary place in the staging file

    int bufferStartOffset = 20;

    uint8_t* transferBuffer = memory;
    int transferStartOffset = bufferStartOffset + bufferLength;
    int transferLength = stagingLength + bufferLength;

    auto cfg = make_unique<StagingConfig>();
    cfg->recordCount = recordCount;

    cfg->storage = storage;
    cfg->storageStartOffset = storageStartOffset;
    cfg->staging = staging;
    cfg->stagingStartOffset = stagingStartOffset;
    cfg->stagingLength = stagingLength;

    cfg->buffer = memoryPtr + transferLength;
    cfg->bufferLength = bufferLength;

    cfg->transferBuffer = memoryPtr;
    cfg->transferLength = transferLength;

    shared_ptr<Provider> stagingProvider = make_shared<StagedProvider>(cfg);
    shared_ptr<Provider> witness = make_shared<Witness>(stagingProvider);
    Consumer c(witness);
    c.consume();

    shared_ptr<Witness> after = dynamic_pointer_cast<Witness>(witness);

    assert(("The count of the before witness should have equaled the count of the after witness" && before->getCount() == after->getCount()));
    assert(("The checksum of the before witness should have equaled the checksum of the after witness" && before->getChecksum() == after->getChecksum()));
}

void testSmall() {
    doTest(123, 8, 50,564,2048);
}

void testMedium() {
    doTest(12003, 8, 50,1024,2048);
}

int main(){
    testSmall();
    testMedium();
}