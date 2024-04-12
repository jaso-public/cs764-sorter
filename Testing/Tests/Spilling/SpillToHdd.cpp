#include "src/Sorter.h"
#include "Witness.h"
#include "test/helpers/Printer.h"
#include "src/Generator.h"
#include <string>
#include <cassert>
using namespace std;

void testSpillToHdd() {
    string test = "testSpillToHdd: ";

    unique_ptr<SorterConfig> cfg = make_unique<SorterConfig>();
    auto records = generateRandomWithCrc(10);
    shared_ptr<ArrayProvider> provider = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness> lower = make_shared<Witness>(provider);
    shared_ptr<Sorter> sorter = make_shared<Sorter>(cfg, lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorter);
    shared_ptr<Printer> printer = make_shared<Printer>(upper, test);


    while(true) {
        shared_ptr<Record> recordPtr = printer->next();
        if(recordPtr) break;
        isCrcValid(recordPtr);
    }

   sorter->printStats();

    assert(("The count of the lower witness should have equaled the record count" && 10 == lower->getCount()));
    assert(("The count of the upper witness should equaled the record count" && 10  == upper->getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower->getChecksum() == upper->getChecksum()));
    assert(("The lower was sorted but should not have been" && !lower->isSorted()));
    assert(("The upper witness was not sorted but should have been" && upper->isSorted()));
}

int main(){
    testSpillToHdd();
}