#include "InOrderGeneratorTest.h"

void InOrderGeneratorTest::testCount10() {
    SorterConfig cfg;
    cfg.recordCount = 10;
    InOrderGenerator generator(cfg);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void InOrderGeneratorTest::testCount50() {
    SorterConfig cfg;
    cfg.recordCount = 50;
    InOrderGenerator generator(cfg);
    for (int i = 0; i < 50; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    InOrderGeneratorTest test;
    test.testCount10();
    test.testCount50();
}