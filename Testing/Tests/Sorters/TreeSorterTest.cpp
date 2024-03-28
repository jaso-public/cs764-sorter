#include "TreeSorterTest.h"

void TreeSorterTest::testCount10() {
    RandomGenerator r(10, 100, 8);
    Witness lower(&r);
    TreeSorter sorter(&lower);
    for (int i = 0; i < 10; i++){
        Record* ptr = sorter.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    Record* ptr = sorter.next();
    assert("Next should have given a null pointer" && ptr == nullptr );

}

void TreeSorterTest::testCount50() {
    RandomGenerator r(10, 100, 8);
    Witness lower(&r);
    TreeSorter sorter(&lower);
    for (int i = 0; i < 50; i++){
        Record* ptr = sorter.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    Record* ptr = sorter.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    TreeSorterTest test;
    test.testCount10();
    test.testCount50();
}