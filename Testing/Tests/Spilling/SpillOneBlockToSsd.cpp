#include "src/Provider.h"
#include "Witness.h"
#include "src/Sorter.h"
#include "src/Consumer.h"
#include "src/Generator.h"
#include <cassert>
#include <string>

void testSpillToSsdFewBlocks() {
    int recordNum = 1024*100;
    unique_ptr<SorterConfig> cfg = make_unique<SorterConfig>();
    auto records = generateRandom(recordNum);
    shared_ptr<ArrayProvider> provider = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness> lower = make_shared<Witness>(provider);
    shared_ptr<Sorter> sorter = make_shared<Sorter>(cfg,lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorter);
    shared_ptr<Dedooper> dooper = make_shared<Dedooper>(upper);
    Consumer consumer(dooper);
    consumer.consume();

    sorter->printStats();

    assert(("The count of the lower witness should have equaled the record count" && recordNum == lower->getCount()));
    assert(("The count of the upper witness should equaled the record count" && recordNum == upper->getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower->getChecksum() == upper->getChecksum()));
    assert(("The lower was sorted but should not have been" && !lower->isSorted()));
    assert(("The upper witness was not sorted but should have been" && upper->isSorted()));
}

int main(){
    testSpillToSsdFewBlocks();
}