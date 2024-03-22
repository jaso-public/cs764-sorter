#include "WitnessTest.h"
#include "Providers/Provider.h"
#include "../TestProviders/InOrderGenerator.h"
#include "Witness.h"
#include "NoopSorter.h"
#include "Consumer.h"
#include "Testing/TestProviders/DropFirst.h"
#include "TreeSorter.h"
#include <cassert>
#include <string>
#include "../TestProviders/Printer.h"
#include "../TestProviders/RandomGenerator.h"
using namespace std;


void WitnessTest::testTenInorder() {
    InOrderGenerator I(10, 100);
    Provider generator = I;
    Witness lower(generator);
    NoopSorter sorter(lower);
    Witness upper(sorter);
    Consumer consumer(upper);
    consumer.consume();

    assert(("The count of the lower witness did not equal the count of the upper but should have", lower.getCount() == upper.getCount()));
    assert(("The count of the upper witness should have been 10", 10 == upper.getCount()));
    assert(("The upper witness should have been sorted but was not", upper.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have",lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testDropOne() {
    InOrderGenerator I(10, 100);
    Provider generator = I;
    Witness lower(generator);
    DropFirst dropper(lower);
    NoopSorter sorter(dropper);
    Witness upper(sorter);
    Consumer consumer(upper);
    consumer.consume();

    assert(("The count of the lower witness should have been 10", 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 9", 9 == upper.getCount()));
    assert(("The upper witness should have been sorted but was not", upper.isSorted));
    assert(("The lower witness should have been sorted but was not", lower.isSorted));
    assert(("The checksum of the lower witness was equal to the checksum of the upper but should not have been", lower.getCrc() != upper.getCrc()));
}

void WitnessTest::testRandomOrder() {
    RandomGenerator r(10, 100);
    Provider generator = r;
    Witness lower(generator);
    NoopSorter sorter(lower);
    Witness upper(sorter);
    Consumer consumer(upper);
    consumer.consume();

    assert(("The count of the lower witness should have been 10", 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10", 10 == upper.getCount()));
    assert(("The upper witness should not have been sorted but was", !upper.isSorted));
    assert(("The lower witness should not have been sorted but was", !lower.isSorted));
    assert(("The checksum of the lower witness was not equal to the checksum of the upper but should have been", lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testTreeSorter() {
    RandomGenerator r(10, 100);
    Provider generator = r;
    Witness lower(generator);
    TreeSorter sorter(lower);
    Witness upper(sorter);
    Consumer consumer(upper);
    consumer.consume();

    assert(("The count of the lower witness should have been 10", 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10", 10 == upper.getCount()));
    assert(("The upper witness should have been sorted but was not", upper.isSorted));
    assert(("The lower witness should not have been sorted but was", !lower.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have",lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testRandomOrderWithPrinting() {
    string test = "testRandomOrderWithPrinting: ";
    RandomGenerator r(10, 100);
    Provider generator = r;
    Printer printer1(generator, test+"from generator");
    Witness lower(printer1);
    NoopSorter sorter(lower);
    Witness upper(sorter);
    Printer printer2(upper, test+"from sorter");
    Consumer consumer(printer2);
    consumer.consume();

    assert(("The count of the lower witness should have been 10", 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10", 10 == upper.getCount()));
    assert(("The upper witness should have not been sorted but was", !upper.isSorted));
    assert(("The lower witness should not have been sorted but was", !lower.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have",lower.getCrc() == upper.getCrc()));
}

void WitnessTest::testTreeSorterWithPrinting() {
    string test = "testTreeSorterWithPrinting: ";
    RandomGenerator r(10, 100);
    Provider generator = r;
    Printer printer1(generator, test+"from generator");
    Witness lower(printer1);
    TreeSorter sorter(lower);
    Witness upper(sorter);
    Printer printer2(upper, test+"from sorter");
    Consumer consumer(printer2);
    consumer.consume();

    assert(("The count of the lower witness should have been 10", 10 == lower.getCount()));
    assert(("The count of the upper witness should have been 10", 10 == upper.getCount()));
    assert(("The upper witness should have not been sorted but was", !upper.isSorted));
    assert(("The lower witness should not have been sorted but was", !lower.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have",lower.getCrc() == upper.getCrc()));
}