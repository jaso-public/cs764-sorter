#include "SpillToHdd.h"
#include "../Config/SorterConfig.h"
#include "../Providers/Provider.h"
#include "../Witness.h"
#include "../Sort/Sorter.h"
#include "TestProviders/Printer.h"
#include <string>
#include <cassert>
using namespace std;

void SpillToHdd::testSpillToHdd() {
    int recordSize = 1000;
    int recordCount = 19000;
    int keyOffset = 8;

    string test = "testSpillToHdd: ";

    SorterConfig cfg;
    cfg.ssdStorageSize = 2*1024*1024;
    cfg.memoryBlockCount = 10;

    //TODO: create CrcRandomGenerator
    CrcRandomGenerator crc(recordCount, recordSize);
    Provider generator(crc);
    Witness lower(generator);
    Sorter sorter(cfg, lower, recordSize, 8);
    Witness upper(sorter);
    Printer p(upper, test);

    while(true) {
        Record* recordPtr = p.next();
        Record record = *recordPtr;
        if(recordPtr) break;
        crc.verifyCrc(record);
    }

    sorter.printStats();

    assert(("The count of the lower witness should have equaled the record count", recordCount == lower.getCount()));
    assert(("The count of the upper witness should equaled the record count", recordCount == upper.getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have", lower.getCrc() == upper.getCrc()));
    assert(("The lower was sorted but should not have been", !lower.isSorted));
    assert(("The upper witness was not sorted but should have been", upper.isSorted));
}