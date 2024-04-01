#include "SpillOneBlockToSsd.h"


SpillOneBlockToSsd::SpillOneBlockToSsd() {};

void SpillOneBlockToSsd::testSpillToSsdFewBlocks() {
    int recordSize = 1024;
    int recordCount = 1024*100;
    int keyOffset = 8;
    int keySize = 8;

    string test = "testSpillToSsdFewBlocks: ";

    RandomGenerator rng(recordCount, recordSize, keyOffset);
    Witness lower(&rng);
    SorterConfig cgf;
    Sorter sorter(cgf, &lower, recordSize, keyOffset, keySize);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

int main(){
    SpillOneBlockToSsd spill;
    spill.testSpillToSsdFewBlocks();
}