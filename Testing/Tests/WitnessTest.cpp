#include "WitnessTest.h"

void WitnessTest::testLower() {
    auto records = generateInOrder(10);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = lower.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = lower.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
    assert("Count should be 10" && lower.getCount() == 10 );
}

void WitnessTest::testWithSorter() {
    auto records = generateInOrder(10);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    NoopSorter sorter(&lower);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = sorter.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = sorter.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void WitnessTest::testGivingWitnessNoopSorter() {
    auto records = generateInOrder(10);
    ArrayProvider provider("name", records);
    NoopSorter sorter(&provider);
    Witness upper(&sorter);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = upper.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = upper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void WitnessTest::testGivingWitnessAnotherWitness() {
    auto records = generateInOrder(10);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    Witness upper(&lower);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = upper.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr2 = upper.next();
    assert("Next should have given a null pointer" && ptr2 == nullptr );
}

void WitnessTest::testUpper() {
    auto records = generateInOrder(10);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = upper.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = upper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void WitnessTest::testTenInorder() {
    auto records = generateInOrder(10);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    Dedooper dooper(&upper);
    Consumer consumer(&dooper);
    consumer.consume();

    assert("The count of the lower witness did not equal the count of the upper but should have" && lower.getCount() == upper.getCount());
    assert("The count of the upper witness should have been 10" && 10 == upper.getCount());
    assert("The upper witness should have been sorted but was not" && upper.isSorted == lower.isSorted);
}

void WitnessTest::testDropOne() {
    auto records = generateInOrder(10);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    DropFirst dropper(&lower);
    NoopSorter sorter(&dropper);
    Witness upper(&sorter);
    Dedooper dooper(&upper);
    Consumer consumer(&dooper);
    consumer.consume();

    assert("The count of the lower witness should have been 10" && 10 == lower.getCount());
    assert("The count of the upper witness should have been 9" && 9 == upper.getCount());
    assert("The upper witness should have been sorted but was not" && upper.isSorted);
    assert("The lower witness should have been sorted but was not" && lower.isSorted);
    assert("The checksum of the lower witness was equal to the checksum of the upper but should not have been" && lower.getCrc() != upper.getCrc());
}

void WitnessTest::testRandomOrder() {
    auto records = generateRandom(10);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    Dedooper dooper(&upper);
    Consumer consumer(&dooper);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper.getCount()));
    assert(("The upper witness should not have been sorted but was" && !upper.isSorted));
    assert(("The lower witness should not have been sorted but was" && !lower.isSorted));
    assert(("The checksum of the lower witness was not equal to the checksum of the upper but should have been" && lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testTreeSorter() {
    auto records = generateRandom(10);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    TreeSorter sorter(&lower);
    Witness upper(&sorter);
    Dedooper dooper(&upper);
    Consumer consumer(&dooper);
    consumer.consume();
    assert(("The count of the lower witness should have been 10" && 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper.getCount()));
    assert(("The upper witness should have been sorted but was not" && upper.isSorted));
    assert(("The lower witness should not have been sorted but was" && !lower.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testRandomOrderWithPrinting() {
    string test = "testRandomOrderWithPrinting: ";
    auto records = generateRandom(10);
    ArrayProvider provider("name", records);
    Printer printer1(&provider, test+"from generator");
    Witness lower(&printer1);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    Dedooper dooper(&upper);
    Printer printer2(&dooper, test+"from sorter");
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
    auto records = generateRandom(10);
    ArrayProvider provider("name", records);
    Printer printer1(&provider, test+"from generator");
    Witness lower(&printer1);
    TreeSorter sorter(&lower);
    Witness upper(&sorter);
    Dedooper dooper(&upper);
    Printer printer2(&dooper, test+"from sorter");
    Consumer consumer(&printer2);
    consumer.consume();

    assert(("The count of the lower witness should have been 10" && 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10" && 10 == upper.getCount()));
    assert(("The upper witness should have been sorted but was" && upper.isSorted));
    assert(("The lower witness should not have been sorted but was" && !lower.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
}

int main(){
    WitnessTest w;
    w.testLower();
    w.testWithSorter();
    w.testGivingWitnessNoopSorter();
    w.testGivingWitnessAnotherWitness();
    w.testUpper();
    w.testTenInorder();
    w.testTreeSorterWithPrinting();
    w.testRandomOrderWithPrinting();
    w.testTreeSorter();
    w.testDropOne();
    w.testRandomOrder();
};