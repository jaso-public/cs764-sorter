#include "RandomGeneratorTest.h"

void RandomGeneratorTest::testCount10() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 10;
    RandomGenerator generator(*cfg);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void RandomGeneratorTest::testCount50() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 50;
    RandomGenerator generator(*cfg);
    for (int i = 0; i < 50; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    RandomGeneratorTest test;
    test.testCount10();
    test.testCount50();
}