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

void testSpill110ToHdd() {
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

void testSorting(string testName, int recordSize, int recordCount){
    Record::staticInitialize(recordSize);

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

    auto provider = make_shared<RandomProvider>(recordCount, false);
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

    assert(("The count of the lower witness should have equaled the record count" && recordCount == lower->getCount()));
    assert(("The count of the upper witness should equaled the record count" && recordCount == upper->getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have"
            && lower->getChecksum() == upper->getChecksum()));
    if (recordCount != 0){
        assert(("The lower was sorted but should not have been" && !lower->isSorted()));
    }
    assert(("The upper witness was not sorted but should have been" && upper->isSorted()));
}


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
    testSpill110ToHdd();
    testSorting("testSmallSort", 20, 20);
    //TODO: testAllMemory fails plus others below
    testSorting("testAllMemory: ", 1000, 9000);
    testSorting("testSpillToSsdFewBlocks: ", 1024, 1024*100);
    testSorting("testSpillToSsd: ", 1000, 900000);
    testSorting("testSpillToLotsOfHddRuns: ", 1000, 190000);
    testSorting("testZeroRecords: ", 1000, 0);
    testSorterConfigInitialization();
}