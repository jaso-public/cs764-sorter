#include "RandomGeneratorTest.h"

void RandomGeneratorTest::testInitializationValues() {
    RandomGenerator r(10, 100, 8);
    assert("Key offset should be 8" && r.keyOffset == 8 );
    assert("Count should be 10" && r.count == 10 );
    assert("Size should be 100" && r.size == 100 );
}

void RandomGeneratorTest::testCount10() {
    RandomGenerator generator(10, 100, 8);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void RandomGeneratorTest::testCount50() {
    RandomGenerator generator(50, 100, 8);
    for (int i = 0; i < 50; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    RandomGeneratorTest test;
    test.testInitializationValues();
    test.testCount10();
    test.testCount50();
}