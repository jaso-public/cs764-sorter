#include <cassert>
#include <string>

#include "./Record.h"
#include "./Provider.h"
#include "./Witness.h"

#include "Sorter.h"

#include "test/helpers/Consumer.h"
#include "test/helpers/Generator.h"
#include "test/helpers/Printer.h"

using namespace std;


void testSmallSort() {
    string testName = "testSmallSort";

    Record::staticInitialize(20, 0, 8);

    auto cfg = make_unique<SorterConfig>();

    shared_ptr<Provider> provider = make_shared<ArrayProvider>(testName, generateRandom(10));
    shared_ptr<Provider> printer1 = make_shared<Printer>(provider, testName+"-before");
    shared_ptr<Provider> lower = make_shared<Witness>(printer1);
    shared_ptr<Provider> sorter = make_shared<Sorter>(cfg, lower);
    shared_ptr<Provider> upper = make_shared<Witness>(sorter);
    shared_ptr<Provider> printer2 = make_shared<Printer>(upper,testName+"-after");

    Consumer consumer(printer2);
    consumer.consume();

    dynamic_pointer_cast<Sorter>(sorter)->printStats();

    shared_ptr<Witness> lowerWitness = dynamic_pointer_cast<Witness>(lower);
    shared_ptr<Witness> upperWitness = dynamic_pointer_cast<Witness>(upper);

    assert(("The count of the lower witness should have equaled the record count" && 10 == lowerWitness->getCount()));
    assert(("The count of the upper witness should equaled the record count" && 10 == upperWitness->getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have"
        && lowerWitness->getChecksum() == upperWitness->getChecksum()));
    assert(("The lower was sorted but should not have been" && !lowerWitness->isSorted()));
    assert(("The upper witness was not sorted but should have been" && upperWitness->isSorted()));
}
//
//void testAllMemory() {
//
//    string test = "testAllMemory: ";
//    SorterConfig* cfg = new SorterConfig();
//    cfg->recordCount = 90000;
//    cfg->recordSize = 1000;
//    auto records = generateRandom(90000);
//    ArrayProvider provider("name", records);
//    Witness lower(&provider);
//    SorterConfig* cfg2 = new SorterConfig();
//    Sorter sorter(*cfg2, &lower);
//    Witness upper(&sorter);
//    Consumer consumer(&upper);
//    consumer.consume();
//
//    sorter.printStats();
//
//    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
//    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
//    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
//    assert(("The lower was sorted but should not have been" && !lower.isSorted));
//    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
//}
//
//void testSpillToSsdFewBlocks() {
//    string test = "testSpillToSsdFewBlocks: ";
//    SorterConfig* cfg = new SorterConfig();
//    cfg->recordCount = 1024*100;
//    cfg->recordSize = 1024;
//    auto records = generateRandom( 1024*100);
//    ArrayProvider provider("name", records);
//    Witness lower(&provider);
//    SorterConfig* cfg2 = new SorterConfig();
//    Sorter sorter(*cfg2, &lower);
//    Witness upper(&sorter);
//    Consumer consumer(&upper);
//    consumer.consume();
//
//    sorter.printStats();
//
//    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
//    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
//    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
//    assert(("The lower was sorted but should not have been" && !lower.isSorted));
//    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
//}
//
//void testSpillToSsd() {
//    string test = "testSpillToSsd: ";
//    SorterConfig* cfg = new SorterConfig();
//    cfg->recordCount = 900000;
//    cfg->recordSize = 1000;
//    auto records = generateRandom( 900000);
//    ArrayProvider provider("name", records);
//    Witness lower(&provider);
//    SorterConfig* cfg2 = new SorterConfig();
//    cfg2->recordCount = 900000;
//    cfg2->recordSize = 1000;
//    Sorter sorter(*cfg2, &lower);
//    Witness upper(&sorter);
//    Consumer consumer(&upper);
//    consumer.consume();
//
//    sorter.printStats();
//
//    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
//    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
//    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
//    assert(("The lower was sorted but should not have been" && !lower.isSorted));
//    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
//}
//
//void testSpillToHdd() {
//    string test = "testSpillToLotsOfHddRuns: ";
//    SorterConfig* cfg = new SorterConfig();
//    cfg->recordCount = 190000;
//    cfg->recordSize = 1000;
//    auto records = generateRandom( 190000);
//    ArrayProvider provider("name", records);
//    Witness lower(&provider);
//    SorterConfig* cfg2 = new SorterConfig();
//    Sorter sorter(*cfg2, &lower);
//    Witness upper(&sorter);
//    Consumer consumer(&upper);
//    consumer.consume();
//
//    sorter.printStats();
//
//    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
//    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
//    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
//    assert(("The lower was sorted but should not have been" && !lower.isSorted));
//    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
//}
//
//void testSpillToLotsOfHddRuns() {
//    string test = "testSpillToLotsOfHddRuns: ";
//    SorterConfig* cfg = new SorterConfig();
//    cfg->recordCount = 190000;
//    cfg->recordSize = 1000;
//    cfg->memoryBlockCount = 10;
//    cfg->memoryBlockSize = 100*1024*1024;
//    auto records = generateRandom( 190000);
//    ArrayProvider provider("name", records);
//    Witness lower(&provider);
//    SorterConfig* cfg2 = new SorterConfig();
//    Sorter sorter(*cfg2, &lower);
//    Witness upper(&sorter);
//    Consumer consumer(&upper);
//    consumer.consume();
//
//    sorter.printStats();
//
//    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
//    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
//    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
//    assert(("The lower was sorted but should not have been" && !lower.isSorted));
//    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
//}
//
//void testZeroRecords() {
//    string test = "testZeroRecords: ";
//    SorterConfig* cfg = new SorterConfig();
//    cfg->recordCount = 0;
//    cfg->recordSize = 1000;
//    auto records = generateRandom( 0);
//    ArrayProvider provider("name", records);
//    Witness lower(&provider);
//    SorterConfig* cfg2 = new SorterConfig();
//    Sorter sorter(*cfg2, &lower);
//    Witness upper(&sorter);
//    Consumer consumer(&upper);
//    consumer.consume();
//
//    sorter.printStats();
//
//    assert(("The count of the lower witness should have equaled 0" && 0 == lower.getCount()));
//    assert(("The count of the upper witness should equaled 0" && 0 == upper.getCount()));
//    assert(("The count of the lower witness should have equaled the record count" && cfg->recordCount == lower.getCount()));
//    assert(("The count of the upper witness should equaled the record count" && cfg->recordCount == upper.getCount()));
//    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
//    assert(("The lower was sorted but should not have been" && !lower.isSorted));
//    assert(("The upper witness was not sorted but should have been" && upper.isSorted));
//}

int main(){
    testSmallSort();
//    testAllMemory();
//    testSpillToSsdFewBlocks();
//    testSpillToSsd();
//    testSpillToHdd();
//    testSpillToLotsOfHddRuns();
//    testZeroRecords();
}