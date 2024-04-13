#include "src/Sorter.h"
#include "Witness.h"
#include "test/helpers/Printer.h"
#include "src/Generator.h"
#include <string>
#include <cassert>
using namespace std;

void testSpillToHdd() {
    string test = "testSpillToHdd: ";
    Record::staticInitialize(100);
    int recordCount = 1;

    unique_ptr<SorterConfig> cfg = make_unique<SorterConfig>();
    cfg->memoryBlockCount = 10;
    cfg->memoryBlockSize = 1000;
    auto ssdDevice = make_shared<IODevice>("ssd.stage");
    auto hddDevice = make_shared<IODevice>("hdd.stage");
//    cfg->ssdDevice = ssdDevice;
//    cfg->hddDevice = hddDevice;



    auto source = make_shared<RandomProvider>(recordCount);
    auto lower = make_shared<Witness>(source);
    auto sorter = make_shared<Sorter>(cfg, lower);
    auto upper = make_shared<Witness>(sorter);
    shared_ptr<Printer> printer = make_shared<Printer>(upper, test);


    while(true) {
        shared_ptr<Record> recordPtr = upper->next();
        if(recordPtr == nullptr) break;
//        isCrcValid(recordPtr);
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

int main(){
    testSpillToHdd();
}