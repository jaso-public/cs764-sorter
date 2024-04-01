#include "SpillToHdd.h"


void SpillToHdd::testSpillToHdd() {
    int recordSize = 1000;
    int recordCount = 19000;
    int keyOffset = 8;
    int keySize = 8;

    string test = "testSpillToHdd: ";

    SorterConfig cfg;
    cfg.ssdStorageSize = 2*1024*1024;
    cfg.memoryBlockCount = 10;

    CrcRandomGenerator crc(recordCount, recordSize, keyOffset, keySize);
    Witness lower(&crc);
    Sorter sorter(cfg, &lower, recordSize, keyOffset, keySize);
    Witness upper(&sorter);
    Printer p(&upper, test);

    while(true) {
        shared_ptr<Record> recordPtr = p.next();
        if(recordPtr) break;
        crc.verifyCrc(recordPtr);
    }

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

int main(){
    SpillToHdd spill;
    spill.testSpillToHdd();
}