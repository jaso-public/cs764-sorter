#include "SorterTest.h"

void SorterTest::testSmallSort() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 10;
    RandomGenerator rng(*cfg);

    string test = "testSmallSort: ";

    Printer printer1(&rng, test+"from generator");
    Witness lower(&printer1);
    SorterConfig* cfg2 = new SorterConfig();
    Sorter sorter(*cfg2, &lower);
    Witness upper(&sorter);
    Printer printer2(&upper, test+"from sorter");
    Consumer consumer(&printer2);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

void SorterTest::testAllMemory() {

    string test = "testAllMemory: ";
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 90000;
    cfg->recordSize = 1000;
    RandomGenerator rng(*cfg);
    Witness lower(&rng);
    SorterConfig* cfg2 = new SorterConfig();
    Sorter sorter(*cfg2, &lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

void SorterTest::testSpillToSsdFewBlocks() {
    string test = "testSpillToSsdFewBlocks: ";
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 1024*100;
    cfg->recordSize = 1024;
    RandomGenerator rng(*cfg);
    Witness lower(&rng);
    SorterConfig* cfg2 = new SorterConfig();
    Sorter sorter(*cfg2, &lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

void SorterTest::testSpillToSsd() {
    string test = "testSpillToSsd: ";
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 900000;
    cfg->recordSize = 1000;
    RandomGenerator rng(*cfg);
    Witness lower(&rng);
    SorterConfig* cfg2 = new SorterConfig();
    cfg2->recordCount = 900000;
    cfg2->recordSize = 1000;
    Sorter sorter(*cfg2, &lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

void SorterTest::testSpillToHdd() {
    string test = "testSpillToLotsOfHddRuns: ";
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 190000;
    cfg->recordSize = 1000;
    RandomGenerator rng(*cfg);
    Witness lower(&rng);
    SorterConfig* cfg2 = new SorterConfig();
    Sorter sorter(*cfg2, &lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

void SorterTest::testSpillToLotsOfHddRuns() {
    string test = "testSpillToLotsOfHddRuns: ";
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 190000;
    cfg->recordSize = 1000;
    cfg->memoryBlockCount = 10;
    cfg->memoryBlockSize = 100*1024*1024;
    RandomGenerator r(*cfg);
    Witness lower(&r);
    SorterConfig* cfg2 = new SorterConfig();
    Sorter sorter(*cfg2, &lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

void SorterTest::testZeroRecords() {
    string test = "testZeroRecords: ";
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 0;
    cfg->recordSize = 1000;
    RandomGenerator rng(*cfg);
    Witness lower(&rng);
    SorterConfig* cfg2 = new SorterConfig();
    Sorter sorter(*cfg2, &lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    sorter.printStats();

    assert(("The count of the lower witness should have equaled 0" && 0 == lower.getCount()));
    assert(("The count of the upper witness should equaled 0" && 0 == upper.getCount()));
    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been" && !lower.isSorted));
    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
}

int main(){
    SorterTest test;
    test.testSmallSort();
//    test.testAllMemory();
//    test.testSpillToSsdFewBlocks();
//    test.testSpillToSsd();
//    test.testSpillToHdd();
//    test.testSpillToLotsOfHddRuns();
//    test.testZeroRecords();
}