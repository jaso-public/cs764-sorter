#include "WitnessTest.h"

void WitnessTest::testLower() {
    InOrderGenerator i(10, 100, 8);
    Witness lower(&i);
    for (int i = 0; i < 10; i++){
        Record* ptr = lower.next();
        assert("Next should have existed" && ptr != nullptr );
        Record r = *ptr;
        r.getRecordKey();
        assert("Record key should not be 0" && r.getRecordKey() != 0 );
    }
    Record* ptr = lower.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
    assert("Count should be 10" && lower.getCount() == 10 );
}

void WitnessTest::testWithSorter() {
    InOrderGenerator i(10, 100, 8);
    Witness lower(&i);
    NoopSorter sorter(&lower);
    for (int i = 0; i < 10; i++){
        Record* ptr = sorter.next();
        assert("Next should have existed" && ptr != nullptr );
        Record r = *ptr;
        r.getRecordKey();
        assert("Record key should not be 0" && r.getRecordKey() != 0 );
    }
    Record* ptr = sorter.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

//TODO: here is the issue, the upper does not like getting the getRecordKey() or completeChecksumCheck() in the next method in Witness.cpp
// this fails when the witness is given the noopsorter as shown in this test
void WitnessTest::testGivingWitnessNoopSorter() {
    InOrderGenerator i(10, 100, 8);
    NoopSorter sorter(&i);
    Witness upper(&sorter);
    for (int i = 0; i < 10; i++){
        Record* ptr = upper.next();
        assert("Next should have existed" && ptr != nullptr );
        Record r = *ptr;
        assert("Record key should not be 0" && r.getRecordKey() != 0 );
    }
    Record* ptr = upper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

//TODO: here is the issue, the upper does not like getting the getRecordKey() or completeChecksumCheck() in the next method in Witness.cpp
// this also fails when the witness is given another witness
void WitnessTest::testGivingWitnessAnotherWitness() {
    InOrderGenerator i(10, 100, 8);
    Witness lower(&i);
    Witness upper(&lower);
    for (int i = 0; i < 10; i++){
        Record* ptr = upper.next();
        assert("Next should have existed" && ptr != nullptr );
        Record r = *ptr;
        assert("Record key should not be 0" && r.getRecordKey() != 0 );
    }
    Record* ptr2 = upper.next();
    assert("Next should have given a null pointer" && ptr2 == nullptr );
}

//TODO: this fails because of the two tests above
void WitnessTest::testUpper() {
    InOrderGenerator i(10, 100, 8);
    Witness lower(&i);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    for (int i = 0; i < 10; i++){
        Record* ptr = upper.next();
        assert("Next should have existed" && ptr != nullptr );
        Record r = *ptr;
        assert("Record key should not be 0" && r.getRecordKey() != 0 );
    }
    Record* ptr = upper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void WitnessTest::testTenInorder() {
    InOrderGenerator i(10, 100, 8);
    Witness lower(&i);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    assert(("The count of the lower witness did not equal the count of the upper but should have" && lower.getCount() == upper.getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper.getCount()));
    assert(("The upper witness should have been sorted but was not" && upper.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testDropOne() {
    InOrderGenerator i(10, 100, 8);
    Witness lower(&i);
    DropFirst dropper(&lower);
    NoopSorter sorter(&dropper);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 9" && 9 == upper.getCount()));
    assert(("The upper witness should have been sorted but was not" && upper.isSorted));
    assert(("The lower witness should have been sorted but was not" && lower.isSorted));
    assert(("The checksum of the lower witness was equal to the checksum of the upper but should not have been" && lower.getCrc() != upper.getCrc()));
}

void WitnessTest::testRandomOrder() {
    RandomGenerator r(10, 100, 8);
    Witness lower(&r);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper.getCount()));
    assert(("The upper witness should not have been sorted but was" && !upper.isSorted));
    assert(("The lower witness should not have been sorted but was" && !lower.isSorted));
    assert(("The checksum of the lower witness was not equal to the checksum of the upper but should have been" && lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testTreeSorter() {
    RandomGenerator r(10, 100, 8);
    Witness lower(&r);
    TreeSorter sorter(&lower);
    Witness upper(&sorter);
    Consumer consumer(&upper);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper.getCount()));
    assert(("The upper witness should have been sorted but was not" && upper.isSorted));
    assert(("The lower witness should not have been sorted but was" && !lower.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testRandomOrderWithPrinting() {
    string test = "testRandomOrderWithPrinting: ";
    RandomGenerator r(10, 100, 8);
    Printer printer1(&r, test+"from generator");
    Witness lower(&printer1);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    Printer printer2(&upper, test+"from sorter");
    Consumer consumer(&printer2);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper.getCount()));
    assert(("The upper witness should have not been sorted but was" && !upper.isSorted));
    assert(("The lower witness should not have been sorted but was" && !lower.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testTreeSorterWithPrinting() {
    string test = "testTreeSorterWithPrinting: ";
    RandomGenerator r(10, 100, 8);
    Printer printer1(&r, test+"from generator");
    Witness lower(&printer1);
    TreeSorter sorter(&lower);
    Witness upper(&sorter);
    Printer printer2(&upper, test+"from sorter");
    Consumer consumer(&printer2);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper.getCount()));
    assert(("The upper witness should have not been sorted but was" && !upper.isSorted));
    assert(("The lower witness should not have been sorted but was" && !lower.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
}

int main(){
    WitnessTest w;
    //w.testLower();
    //w.testWithSorter();
//TODO: stuck on these lower 3 tests
      w.testGivingWitnessNoopSorter();
      w.testGivingWitnessAnotherWitness();
      w.testUpper();
//    w.testTenInorder();
//    w.testTreeSorterWithPrinting();
//    w.testRandomOrderWithPrinting();
//    w.testTreeSorter();
//    w.testDropOne();
//    w.testRandomOrder();
};