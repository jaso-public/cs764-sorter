#include "InOrderGeneratorTest.h"

void InOrderGeneratorTest::testInitializationValues() {
    InOrderGenerator i(10, 100, 8, 8);
    assert("Key offset should be 8" && i.keyOffset == 8 );
    assert("Count should be 10" && i.count == 10 );
    assert("Size should be 100" && i.size == 100 );
}

void InOrderGeneratorTest::testCount10() {
    InOrderGenerator generator(10, 100, 8, 8);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void InOrderGeneratorTest::testCount50() {
    InOrderGenerator generator(50, 100, 8, 8);
    for (int i = 0; i < 50; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    InOrderGeneratorTest test;
    test.testInitializationValues();
    test.testCount10();
    test.testCount50();
}