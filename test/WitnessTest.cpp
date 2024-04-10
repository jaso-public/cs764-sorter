#include <cassert>
#include <string>

#include "Record.h"
#include "Provider.h"
#include "Witness.h"

#include "src/Consumer.h"
#include "test/helpers/Generator.h"
#include "test/helpers/Printer.h"


#include "test/helpers/NoopSorter.h"
#include "Testing/TestProviders/DropFirst.h"
#include "test/helpers/TreeSorter.h"

using namespace std;


void testLower() {
    auto records = generateInOrder(10);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    auto lower = make_shared<Witness>(source);

    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = lower->next();
        assert("Next should have existed" && ptr != nullptr );
    }

    shared_ptr<Record> ptr = lower->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
    assert("Count should be 10" && lower->getCount() == 10 );
}

void testWithSorter() {
    auto records = generateInOrder(10);
    shared_ptr<Provider> provider = make_shared<ArrayProvider>("name", records);
    shared_ptr<Provider> lower = make_shared<Witness>(provider);
    shared_ptr<Provider> sorter = make_shared<NoopSorter>(lower);

    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = sorter->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = sorter->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testGivingWitnessNoopSorter() {
    auto records = generateInOrder(10);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    shared_ptr<Provider> sorter = make_shared<NoopSorter>(source);
    shared_ptr<Provider> upper = make_shared<Witness>(sorter);

    for (int i = 0; i < 10; i++){
        auto ptr = upper->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = upper->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testGivingWitnessAnotherWitness() {
    auto records = generateInOrder(10);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    shared_ptr<Provider> lower = make_shared<Witness>(source);
    shared_ptr<Provider> upper = make_shared<Witness>(lower);

    for (int i = 0; i < 10; i++){
        auto ptr = upper->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr2 = upper->next();
    assert("Next should have given a null pointer" && ptr2 == nullptr );
}

void testUpper() {
    auto records = generateInOrder(10);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    shared_ptr<Provider> lower = make_shared<Witness>(source);
    shared_ptr<Provider> sorter = make_shared<NoopSorter>(lower);
    shared_ptr<Provider> upper = make_shared<Witness>(sorter);

    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = upper->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = upper->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testTenInorder() {
    auto records = generateInOrder(10);
    shared_ptr<ArrayProvider> providerPtr = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness> lower = make_shared<Witness>(providerPtr);
    shared_ptr<NoopSorter> sorterPtr = make_shared<NoopSorter>(lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorterPtr);
    Consumer consumer(upper);
    consumer.consume();

    assert("The count of the lower witness did not equal the count of the upper but should have" && lower->getCount() == upper->getCount());
    assert("The count of the upper witness should have been 10" && 10 == upper->getCount());
    assert("The upper witness should have been sorted but was not" && upper->isSorted() == lower->isSorted());
}

void testDropOne() {
    auto records = generateInOrder(10);
    shared_ptr<ArrayProvider> providerPtr = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness> lower = make_shared<Witness>(providerPtr);
    shared_ptr<DropFirst> dropper = make_shared<DropFirst>(lower);
    shared_ptr<NoopSorter> sorterPtr = make_shared<NoopSorter>(dropper);
    shared_ptr<Witness> upper = make_shared<Witness>(sorterPtr);
    Consumer consumer(upper);
    consumer.consume();

    assert("The count of the lower witness should have been 10" && 10 == lower->getCount());
    assert("The count of the upper witness should have been 9" && 9 == upper->getCount());
    assert("The upper witness should have been sorted but was not" && upper->isSorted());
    assert("The lower witness should have been sorted but was not" && lower->isSorted());
    assert("The checksum of the lower witness was equal to the checksum of the upper but should not have been" && lower->getChecksum() != upper->getChecksum());
}



void testRandomOrder() {
    auto records = generateRandom(10);
    shared_ptr<ArrayProvider> providerPtr = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness> lower = make_shared<Witness>(providerPtr);
    shared_ptr<NoopSorter> sorterPtr = make_shared<NoopSorter>(lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorterPtr);
    Consumer consumer(upper);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower->getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper->getCount()));
    assert(("The upper witness should not have been sorted but was" && !upper->isSorted()));
    assert(("The lower witness should not have been sorted but was" && !lower->isSorted()));
    assert(("The checksum of the lower witness was not equal to the checksum of the upper but should have been" && lower->getChecksum() == upper->getChecksum()));
}

void testTreeSorter() {
    auto records = generateRandom(10);
    ArrayProvider provider("name", records);
    shared_ptr<ArrayProvider> providerPtr = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness> lower = make_shared<Witness>(providerPtr);
    shared_ptr<TreeSorter> sorterPtr = make_shared<TreeSorter>(lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorterPtr);
    Consumer consumer(upper);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower->getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper->getCount()));
    assert(("The upper witness should have been sorted but was not" && upper->isSorted()));
    assert(("The lower witness should not have been sorted but was" && !lower->isSorted()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower->getChecksum() == upper->getChecksum()));
}

void testRandomOrderWithPrinting() {
    string test = "testRandomOrderWithPrinting: ";
    auto records = generateRandom(10);
    shared_ptr<ArrayProvider> providerPtr = make_shared<ArrayProvider>("name", records);
    shared_ptr<Printer> printer1 = make_shared<Printer>(providerPtr, test+"from generator");
    shared_ptr<Witness> lower = make_shared<Witness>(printer1);
    shared_ptr<NoopSorter> sorterPtr = make_shared<NoopSorter>(lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorterPtr);
     shared_ptr<Printer> printer2 = make_shared<Printer>(upper, test+"from sorter");
    Consumer consumer(printer2);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower->getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper->getCount()));
    assert(("The upper witness should have not been sorted but was" && !upper->isSorted()));
    assert(("The lower witness should not have been sorted but was" && !lower->isSorted()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower->getChecksum() == upper->getChecksum()));
}

void testTreeSorterWithPrinting() {
    string test = "testTreeSorterWithPrinting: ";
    auto records = generateRandom(10);
    shared_ptr<ArrayProvider> providerPtr = make_shared<ArrayProvider>("name", records);
    shared_ptr<Printer> printer1 = make_shared<Printer>(providerPtr, test+"from generator");
    shared_ptr<Witness> lower = make_shared<Witness>(printer1);
    shared_ptr<TreeSorter> sorterPtr = make_shared<TreeSorter>(lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorterPtr);
    shared_ptr<Printer> printer2 = make_shared<Printer>(upper, test+"from sorter");
    Consumer consumer(printer2);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower->getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper->getCount()));
    assert(("The upper witness should have been sorted but was" && upper->isSorted()));
    assert(("The lower witness should not have been sorted but was" && !lower->isSorted()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower->getChecksum() == upper->getChecksum()));
}

int main() {
    testLower();
    testWithSorter();
    testGivingWitnessNoopSorter();
    testGivingWitnessAnotherWitness();
    testUpper();
    testTenInorder();
    testTreeSorterWithPrinting();
    testRandomOrderWithPrinting();
    testTreeSorter();
    testDropOne();
    testRandomOrder();
};