#include "SpillOneBlockToSsd.h"


SpillOneBlockToSsd::SpillOneBlockToSsd() {};

void SpillOneBlockToSsd::testSpillToSsdFewBlocks() {
    string test = "testSpillToSsdFewBlocks: ";
    SorterConfig cfg;
    cfg.recordCount = 1024*100;
    cfg.recordSize = 1024;
    RandomGenerator rng(cfg);
    Witness lower(&rng);
    SorterConfig cgf;
    Sorter sorter(cgf, &lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && cfg.recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && cfg.recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

int main(){
    SpillOneBlockToSsd spill;
    spill.testSpillToSsdFewBlocks();
}