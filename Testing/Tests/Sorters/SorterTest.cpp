#include "SorterTest.h"

void SorterTest::testSmallSort() {
    int recordSize = 100;
    int recordCount = 10;
    int keyOffset = 8;

    string test = "testSmallSort: ";

    RandomGenerator rng(keyOffset, recordCount, recordSize);
    Printer printer1(&rng, test+"from generator");
    Witness lower(&printer1);
    SorterConfig cgf;
    Sorter sorter(cgf, &lower, recordSize, keyOffset);
    Witness upper(&sorter);
    Printer printer2(&upper, test+"from sorter");
    Consumer consumer(&printer2);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

void SorterTest::testAllMemory() {
    int recordSize = 1000;
    int recordCount = 90000;
    int keyOffset = 8;

    string test = "testAllMemory: ";

    RandomGenerator rng(keyOffset, recordCount, recordSize);
    Witness lower(&rng);
    SorterConfig cgf;
    Sorter sorter(cgf, &lower, recordSize, keyOffset);
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

void SorterTest::testSpillToSsdFewBlocks() {
    int recordSize = 1024;
    int recordCount = 1024*100;
    int keyOffset = 8;

    string test = "testSpillToSsdFewBlocks: ";

    RandomGenerator rng(keyOffset, recordCount, recordSize);
    Witness lower(&rng);
    SorterConfig cgf;
    Sorter sorter(cgf, &lower, recordSize, keyOffset);
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

void SorterTest::testSpillToSsd() {
    int recordSize = 1000;
    int recordCount = 900000;
    int keyOffset = 8;

    string test = "testSpillToSsd: ";

    RandomGenerator rng(keyOffset, recordCount, recordSize);
    Witness lower(&rng);
    SorterConfig cgf;
    Sorter sorter(cgf, &lower, recordSize, keyOffset);
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

void SorterTest::testSpillToHdd() {
    int recordSize = 1000;
    int recordCount = 190000;
    int keyOffset = 8;

    string test = "testSpillToLotsOfHddRuns: ";

    RandomGenerator rng(keyOffset, recordCount, recordSize);
    Witness lower(&rng);
    SorterConfig cgf;
    Sorter sorter(cgf, &lower, recordSize, keyOffset);
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

void SorterTest::testSpillToLotsOfHddRuns() {
    int recordSize = 1000;
    int recordCount = 190000;
    int keyOffset = 8;

    string test = "testSpillToLotsOfHddRuns: ";

    SorterConfig cfg;
    cfg.ssdStorageSize = 100*1024*1024;
    cfg.memoryBlockCount = 10;

    RandomGenerator r(recordCount, recordSize);
    Witness lower(&r);
    Sorter sorter(cfg, &lower, recordSize, keyOffset);
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

void SorterTest::testZeroRecords() {
    int recordSize = 1000;
    int recordCount = 0;
    int keyOffset = 8;

    string test = "testZeroRecords: ";

    RandomGenerator rng(keyOffset, recordCount, recordSize);
    Witness lower(&rng);
    SorterConfig cgf;
    Sorter sorter(cgf, &lower, recordSize, keyOffset);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled 0" && 0 == lower.getCount()));
    assert(("The count of the upper witness should equaled 0" && 0 == upper.getCount()));
    assert(("The count of the lower witness should have equaled the record count" && recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

int main(){
    SorterTest test;
    test.testSmallSort();
    test.testAllMemory();
    test.testSpillToSsdFewBlocks();
    test.testSpillToSsd();
    test.testSpillToHdd();
    test.testSpillToLotsOfHddRuns();
    test.testZeroRecords();
}