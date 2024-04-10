#include "src/Sorter.h"
#include "../../src/Witness.h"
#include "src/Consumer.h"
#include "test/helpers/Generator.h"
#include <cassert>
#include <string>


void testSpillToLotsOfHddRuns() {
    unique_ptr<SorterConfig> cfg = make_unique<SorterConfig>();

    auto records = generateRandomWithCrc(10);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness>  lower = make_shared<Witness>(source);
    shared_ptr<Sorter> sorter = make_shared<Sorter>(cfg, lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorter);
    shared_ptr<Dedooper> dooper = make_shared<Dedooper>(upper);
    Consumer consumer(dooper);
    consumer.consume();

    sorter->printStats();

    assert(("The record count was not equal to the count of the lower witness" && 10 == lower->getCount()));
    assert(("The record count was not equal to the count of the upper witness" && 10 ==  upper->getCount()));
    assert(("The lower checksum was not equal to the upper checksum" && lower->getChecksum() == upper->getChecksum()));
    assert(("The lower witness should not have been sorted but was" && !lower->isSorted()));
    assert(("The upper witness was not sorted but should have been" && upper->isSorted()));
}

int main(){
    testSpillToLotsOfHddRuns();
}
