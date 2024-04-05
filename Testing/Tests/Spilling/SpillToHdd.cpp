#include "SpillToHdd.h"


void SpillToHdd::testSpillToHdd() {
    string test = "testSpillToHdd: ";

    SorterConfig* cfg = new SorterConfig();
    cfg->ssdStorageSize = 2*1024*1024;
    cfg->memoryBlockCount = 10;
    cfg->recordSize = 1000;
    cfg->recordCount = 19000;
    cfg->keyOffset = 8;
    cfg->keySize = 8;

    CrcRandomGenerator crc(*cfg);
    Witness lower(&crc);
    Sorter sorter(*cfg, &lower);
    Witness upper(&sorter);
    Printer p(&upper, test);

    while(true) {
        shared_ptr<Record> recordPtr = p.next();
        if(recordPtr) break;
        crc.verifyCrc(recordPtr);
    }

   sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount  == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

int main(){
    SpillToHdd spill;
    spill.testSpillToHdd();
}