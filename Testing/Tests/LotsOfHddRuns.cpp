#include "LotsOfHddRuns.h"

void LotsOfHddRuns::testSpillToLotsOfHddRuns() {
    int recordSize = 1000;
    int recordCount = 190000;
    int keyOffset = 8;

    string test = "testSpillToLotsOfHddRuns: ";

    SorterConfig cfg;
    cfg.ssdStorageSize = 100*1024*1024;
    cfg.memoryBlockCount = 10;

    CrcRandomGenerator crc(recordCount, recordSize, keyOffset);
    Witness lower(&crc);
    Sorter sorter(cfg, &lower, recordSize, keyOffset);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The record count was not equal to the count of the lower witness" && recordCount == lower.getCount()));
    assert(("The record count was not equal to the count of the upper witness" && recordCount ==  upper.getCount()));
    assert(("The lower checksum was not equal to the upper checksum" && lower.getCrc() == upper.getCrc()));
    assert(("The lower witness should not have been sorted but was" && !lower.checkSorted()));
    assert(("The upper witness was not sorted but should have been" && upper.checkSorted()));
}

int main(){
    LotsOfHddRuns runs;
    runs.testSpillToLotsOfHddRuns();
}
