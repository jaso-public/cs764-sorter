#include "LotsOfHddRuns.h"


void LotsOfHddRuns::testSpillToLotsOfHddRuns() {
    string test = "testSpillToLotsOfHddRuns: ";

    SorterConfig* cfg = new SorterConfig();
    cfg->recordSize = 1000;
    cfg->recordCount = 190000;
    cfg->ssdStorageSize = 100*1024*1024;
    cfg->memoryBlockCount = 10;

    CrcRandomGenerator crc(*cfg);
    Witness lower(&crc);
    Sorter sorter(*cfg, &lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The record count was not equal to the count of the lower witness" && cfg->recordCount == lower.getCount()));
    assert(("The record count was not equal to the count of the upper witness" && cfg->recordCount ==  upper.getCount()));
    assert(("The lower checksum was not equal to the upper checksum" && lower.getCrc() == upper.getCrc()));
    assert(("The lower witness should not have been sorted but was" && !lower.checkSorted()));
    assert(("The upper witness was not sorted but should have been" && upper.checkSorted()));
}

int main(){
    LotsOfHddRuns runs;
    runs.testSpillToLotsOfHddRuns();
}
