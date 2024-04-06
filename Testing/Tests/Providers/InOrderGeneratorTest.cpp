#include "InOrderGeneratorTest.h"

void InOrderGeneratorTest::testCount10() {
    auto records = generateInOrder(10);
    ArrayProvider generator("name", records);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void InOrderGeneratorTest::testCount50() {
    auto records = generateInOrder(50);
    ArrayProvider generator("name", records);
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