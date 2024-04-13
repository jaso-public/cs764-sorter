#include "src/Sorter.h"
#include "../../src/Witness.h"
#include "../../src/Provider.h"
#include "src/Consumer.h"
#include <cassert>


void testSpillToLotsOfHddRuns() {
    unique_ptr<SorterConfig> cfg = make_unique<SorterConfig>();

    auto source = make_shared<RandomProvider>(10);
    auto lower = make_shared<Witness>(source);
    auto sorter = make_shared<Sorter>(cfg, lower);
    auto upper = make_shared<Witness>(sorter);
    auto consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    sorter->writeStats(std::cout);

    assert(("The record count was not equal to the count of the lower witness" && 10 == lower->getCount()));
    assert(("The record count was not equal to the count of the upper witness" && 10 ==  upper->getCount()));
    assert(("The lower checksum was not equal to the upper checksum" && lower->getChecksum() == upper->getChecksum()));
    assert(("The lower witness should not have been sorted but was" && !lower->isSorted()));
    assert(("The upper witness was not sorted but should have been" && upper->isSorted()));
}

int main(){
    testSpillToLotsOfHddRuns();
}
