#include <cassert>
#include <string>

#include "Record.h"
#include "Provider.h"
#include "Witness.h"
#include "Consumer.h"

#include "test/helpers/Printer.h"
#include "test/helpers/TreeSorter.h"

using namespace std;


void testLower() {
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
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
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
    shared_ptr<Provider> lower = make_shared<Witness>(source);

    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = lower->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = lower->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testGivingWitnessNoopSorter() {
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
    shared_ptr<Provider> upper = make_shared<Witness>(source);

    for (int i = 0; i < 10; i++){
        auto ptr = upper->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = upper->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testGivingWitnessAnotherWitness() {
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
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
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
    shared_ptr<Provider> lower = make_shared<Witness>(source);
    shared_ptr<Provider> upper = make_shared<Witness>(lower);

    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = upper->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = upper->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testTenInorder() {
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
    shared_ptr<Witness> lower = make_shared<Witness>(source);
    shared_ptr<Witness> upper = make_shared<Witness>(lower);
    shared_ptr<NoopConsumer> consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    assert("The count of the lower witness did not equal the count of the upper but should have" && lower->getCount() == upper->getCount());
    assert("The count of the upper witness should have been 10" && 10 == upper->getCount());
    assert("The upper witness should have been sorted but was not" && upper->isSorted() == lower->isSorted());
}

void testDropOne() {
    int recordCount = 10;
    shared_ptr<Provider> source = make_shared<RandomProvider>(recordCount);
    shared_ptr<Witness> lower = make_shared<Witness>(source);
    shared_ptr<DropFirst> dropper = make_shared<DropFirst>(lower);
    shared_ptr<Witness> upper = make_shared<Witness>(dropper);
    shared_ptr<NoopConsumer> consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    assert("The count of the lower witness should have been 10" && recordCount == lower->getCount());
    assert("The count of the upper witness should have been 9" && recordCount-1 == upper->getCount());
//    assert("The upper witness should have been sorted but was not" && upper->isSorted());
//    assert("The lower witness should have been sorted but was not" && lower->isSorted());
//    assert("The checksum of the lower witness was equal to the checksum of the upper but should not have been" && lower->getChecksum() != upper->getChecksum());
}



void testRandomOrder() {
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
    shared_ptr<Witness> lower = make_shared<Witness>(source);
    shared_ptr<Witness> upper = make_shared<Witness>(lower);
    shared_ptr<NoopConsumer> consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower->getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper->getCount()));
    assert(("The upper witness should not have been sorted but was" && !upper->isSorted()));
    assert(("The lower witness should not have been sorted but was" && !lower->isSorted()));
    assert(("The checksum of the lower witness was not equal to the checksum of the upper but should have been" && lower->getChecksum() == upper->getChecksum()));
}

void testTreeSorter() {
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
    shared_ptr<Witness> lower = make_shared<Witness>(source);
    shared_ptr<TreeSorter> sorterPtr = make_shared<TreeSorter>(lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorterPtr);
    shared_ptr<NoopConsumer> consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower->getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper->getCount()));
    assert(("The upper witness should have been sorted but was not" && upper->isSorted()));
    assert(("The lower witness should not have been sorted but was" && !lower->isSorted()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower->getChecksum() == upper->getChecksum()));
}

void testRandomOrderWithPrinting() {
    string test = "testRandomOrderWithPrinting: ";
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
    shared_ptr<Printer> printer1 = make_shared<Printer>(source, test+"from generator");
    shared_ptr<Witness> lower = make_shared<Witness>(printer1);
    shared_ptr<Witness> upper = make_shared<Witness>(lower);
    shared_ptr<Printer> printer2 = make_shared<Printer>(upper, test+"from sorter");
    shared_ptr<NoopConsumer> consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower->getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper->getCount()));
    assert(("The upper witness should have not been sorted but was" && !upper->isSorted()));
    assert(("The lower witness should not have been sorted but was" && !lower->isSorted()));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower->getChecksum() == upper->getChecksum()));
}

void testTreeSorterWithPrinting() {
    string test = "testTreeSorterWithPrinting: ";
    shared_ptr<Provider> source = make_shared<RandomProvider>(10);
    shared_ptr<Printer> printer1 = make_shared<Printer>(source, test+"from generator");
    shared_ptr<Witness> lower = make_shared<Witness>(printer1);
    shared_ptr<TreeSorter> sorterPtr = make_shared<TreeSorter>(lower);
    shared_ptr<Witness> upper = make_shared<Witness>(sorterPtr);
    shared_ptr<Printer> printer2 = make_shared<Printer>(upper, test+"from sorter");
    shared_ptr<NoopConsumer> consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

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
//    testTreeSorterWithPrinting();
//    testRandomOrderWithPrinting();
    testTreeSorter();
    testDropOne();
    testRandomOrder();
};