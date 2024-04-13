#include <cassert>
#include <string>

#include "./Record.h"
#include "./Provider.h"
#include "./Witness.h"

#include "Sorter.h"

#include "src/Consumer.h"
#include "src/Generator.h"
#include "test/helpers/Printer.h"

using namespace std;

void testSpillToHdd() {
    string test = "testSpillToHdd: ";
    Record::staticInitialize(100);
    int recordCount = 110;

    unique_ptr<SorterConfig> cfg = make_unique<SorterConfig>();
    cfg->memoryBlockCount = 10;
    cfg->memoryBlockSize = 1000;
    auto ssdDevice = make_shared<IODevice>("ssd.stage");
    auto hddDevice = make_shared<IODevice>("hdd.stage");
    cfg->ssdDevice = ssdDevice;
    cfg->hddDevice = hddDevice;
    cfg->hddReadSize = 1000;
    cfg->ssdReadSize = 500;
    cfg->ssdStorageSize = 50000;



    auto source = make_shared<RandomProvider>(recordCount);
    auto lower = make_shared<Witness>(source);
    auto sorter = make_shared<Sorter>(cfg, lower);
    auto upper = make_shared<Witness>(sorter);
    shared_ptr<Printer> printer = make_shared<Printer>(upper, test);


    while(true) {
        shared_ptr<Record> recordPtr = upper->next();
        if(recordPtr == nullptr) break;
        isCrcValid(recordPtr);
    }
    std::ostream* out = &std::cout;

    sorter->writeStats(*out);
    lower->writeStats(*out, "pre-sort");
    upper->writeStats(*out, "post-sort");
    ssdDevice->writeStats(*out);
    hddDevice->writeStats(*out);

    assert(("The count of the lower witness should have equaled the record count" && recordCount == lower->getCount()));
    assert(("The count of the upper witness should equaled the record count" && recordCount  == upper->getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower->getChecksum() == upper->getChecksum()));
    assert(("The lower was sorted but should not have been" && !lower->isSorted()));
    assert(("The upper witness was not sorted but should have been" && upper->isSorted()));
}


void testSmallSort() {
    string testName = "testSmallSort";
    int count = 20;

    Record::staticInitialize(20);

    auto cfg = make_unique<SorterConfig>();

    auto provider = make_shared<RandomProvider>(count, false);
    auto printer1 = make_shared<Printer>(provider, testName+"-before");
    auto lower = make_shared<Witness>(printer1);
    auto sorter = make_shared<Sorter>(cfg, lower);
    auto upper = make_shared<Witness>(sorter);
    auto printer2 = make_shared<Printer>(upper,testName+"-after");

    auto device = make_shared<IODevice>("output.txt");
    auto consumer = make_shared<DeviceConsumer>(printer2, device, 256 * 1024);
    consumer->consume();

    std::ostream* out = &std::cout;
    device->writeStats(*out);

    assert(("The count of the lower witness should have equaled the record count" && count == lower->getCount()));
    assert(("The count of the upper witness should equaled the record count" && count == upper->getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have"
        && lower->getChecksum() == upper->getChecksum()));
    assert(("The lower was sorted but should not have been" && !lower->isSorted()));
    assert(("The upper witness was not sorted but should have been" && upper->isSorted()));
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


void testSorterConfigInitialization() {
    SorterConfig config;
    assert("Fraction was not right" && config.fraction ==  0.005F );
    assert("memoryBlockSize was not right" && config.memoryBlockSize == 1024 * 1024 );
    assert("memoryBlockCount was not right" && config.memoryBlockCount ==  100 );
    assert("ssdReadSize was not right" && config.ssdReadSize ==  16 * 1024);
    assert("ssdStorageSize was not right" && config.ssdStorageSize == 10L * 1024 * 1024 * 1024);
    assert("hddReadSize was not right" && config.hddReadSize ==  256 * 1024 );
    assert("Could not access ssdDevice" && config.ssdDevice == nullptr);
    assert("Could not access hddDevice" && config.hddDevice == nullptr);
}


int main() {
    testSpillToHdd();
//    testSorterConfigInitialization();
//    testSmallSort();
//    testAllMemory();
//    testSpillToSsdFewBlocks();
//    testSpillToSsd();
//    testSpillToHdd();
//    testSpillToLotsOfHddRuns();
//    testZeroRecords();
}