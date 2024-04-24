#include <cassert>
#include <string>

#include "./Record.h"
#include "./Provider.h"
#include "./Witness.h"

#include "Sorter.h"

#include "src/Consumer.h"
#include "src/Generator.h"
#include "test/helpers/Printer.h"
#include "./src/tools/Generate.h"
#include "./src/tools/SortMain.h"

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

    auto provider = make_shared<RandomProvider>(recordCount);
    auto printer1 = make_shared<Printer>(provider, testName+"-before");
    auto lower = make_shared<Witness>(provider);
    auto sorter = make_shared<Sorter>(cfg, lower);
    auto upper = make_shared<Witness>(sorter);
    auto consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    std::ostream* out = &std::cout;

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

void test120GBdiv1000() {

    std::ostream* out = &std::cout;  // Default to cout

    string ssdStagingFileName = "ssd.staging";
    string hddStagingFileName = "hdd.staging";

    uint32_t recordSize = 128;

    uint64_t cacheSize = 1L * 1024 * 1024;
    uint64_t memorySize = 100L * 1024 * 1024;
    uint64_t ssdSize = 10L * 1024 * 1024 * 1024;

    uint32_t ssdReadSize = 16 * 1024;
    uint32_t hddReadSize = 256 * 1024;


    recordSize = 8;
    Record::staticInitialize(recordSize);

    auto cfg = make_unique<SorterConfig>();
    auto ssdDevice = make_shared<IODevice>(ssdStagingFileName);
    auto hddDevice = make_shared<IODevice>(hddStagingFileName);

    cfg->ssdDevice = ssdDevice;
    cfg->hddDevice = hddDevice;
    cfg->memoryBlockSize = cacheSize / 1024;
    cfg->memoryBlockCount = memorySize / cacheSize;
    cfg->ssdStorageSize = ssdSize / 1024;
    cfg->ssdReadSize = ssdReadSize / 1024;
    cfg->hddReadSize = hddReadSize / 1024;

    cfg->writeStats(*out);

    uint64_t numberOrRecords = 40 * 1024 * 1024 / recordSize;
    auto provider = make_shared<RandomProvider>(numberOrRecords);
    auto lower = make_shared<Witness>(provider);
    auto sorter = make_shared<Sorter>(cfg, lower);
    auto upper = make_shared<Witness>(sorter);
    auto consumer = make_shared<NoopConsumer>(upper);

    consumer->consume();

    sorter->writeStats(*out);
    lower->writeStats(*out, "pre-sort");
    upper->writeStats(*out, "post-sort");
    ssdDevice->writeStats(*out);
    hddDevice->writeStats(*out);
}

/**
 * This test will generate an input file with the following characteristics
 * @param recordSize size of each record
 * @param recordCount total records to generate
 * @param probability the probability of total records to make fall in range
 * @param range range to generate the specified probability of records in
 * @param name the name of the input file to place the generated records in
 */
void testGenerate(int recordSize, int recordCount, double probability, int range, string fileName) {
    const char* generateArgs[] = {"generate", "-s", nullptr,"-c", nullptr, "-f", nullptr, "-p", nullptr, "-r", nullptr};
    generateArgs[2] = to_string(recordSize).c_str();
    generateArgs[4] = to_string(recordCount).c_str();
    generateArgs[6] = fileName.c_str();
    generateArgs[8] = to_string(probability).c_str();
    generateArgs[10] = to_string(range).c_str();
    int generateArgsCount = sizeof(generateArgs) / sizeof(generateArgs[0]);
    generateMain(generateArgsCount, const_cast<char**>(generateArgs));
}

/**
 * This test will sort any input file
 * @param recordSize the size of a record
 * @param fileName the name of the input file to sort
 */
void testSort(int recordSize, string fileName, bool deleteInput){
    string outFile = "test-output.txt";
    string ssdStagingFile = "test-ssd-staging.txt";
    string hddStagingFile = "test-hdd-staging.txt";
    const char* sortArgs[] = {"sort", "-j", nullptr, "-g", nullptr, "-h", nullptr, "-s", nullptr, "-i", nullptr, "-d"};
    sortArgs[2] = outFile.c_str();
    sortArgs[4] = ssdStagingFile.c_str();
    sortArgs[6] = hddStagingFile.c_str();
    sortArgs[8] = to_string(recordSize).c_str();
    sortArgs[10] = fileName.c_str();
    int sortArgsCount = sizeof(sortArgs) / sizeof(sortArgs[0]);
    sortMain(sortArgsCount,const_cast<char**>(sortArgs));
    remove(outFile.c_str());
    remove(ssdStagingFile.c_str());
    remove(hddStagingFile.c_str());
    if (deleteInput){
        remove(fileName.c_str());
    }
}

int main() {
//    testSpill110ToHdd();
//    testSorting("testSmallSort", 20, 20);
//    testSorting("testAllMemory: ", 1000, 9000);
//    testSorting("testSpillToSsdFewBlocks: ", 1024, 1024*100);
//    testSorting("testSpillToSsd: ", 1000, 900000);
//    testSorting("testSpillToLotsOfHddRuns: ", 1000, 190000);
//    testSorting("testZeroRecords: ", 1000, 0);
//    testSorterConfigInitialization();

   // test120GBdiv1000();
    testGenerate(20, 100, 0.01, 999, "test-input.txt");
    testSort( 20, "test-input.txt", false);
}