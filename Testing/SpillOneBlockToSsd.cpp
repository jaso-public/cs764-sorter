#include "src/Provider.h"
#include "Witness.h"
#include "src/Sorter.h"
#include "src/Consumer.h"
#include <cassert>

void testSpillToSsdFewBlocks() {
    int recordNum = 1024*100;
    unique_ptr<SorterConfig> cfg = make_unique<SorterConfig>();

    auto source = make_shared<RandomProvider>(recordNum);
    auto lower = make_shared<Witness>(source);
    auto sorter = make_shared<Sorter>(cfg, lower);
    auto upper = make_shared<Witness>(sorter);
    auto consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    sorter->writeStats(std::cout);

    assert(("The count of the lower witness should have equaled the record count" && recordNum == lower->getCount()));
    assert(("The count of the upper witness should equaled the record count" && recordNum  == upper->getCount()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower->getChecksum() == upper->getChecksum()));
    assert(("The lower was sorted but should not have been" && !lower->isSorted()));
    assert(("The upper witness was not sorted but should have been" && upper->isSorted()));
}

int main(){
    testSpillToSsdFewBlocks();
}