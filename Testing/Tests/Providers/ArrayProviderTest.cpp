#include "ArrayProviderTest.h"

void ArrayProviderTest::testGenerating10Records() {
    InOrderGenerator generator(10, 100, 8, 8);
    vector<Record> records(10);
    for (int i=0; i<10; i++){
        shared_ptr<Record> r = generator.next();
        records.push_back(*r);
    }
    ArrayProvider provider("name", records);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = provider.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = provider.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void ArrayProviderTest::testGenerating50Records() {
    InOrderGenerator generator(50, 100, 8, 8);
    vector<Record> records(50);
    for (int i=0; i<50; i++){
        shared_ptr<Record>  r = generator.next();
        records.push_back(*r);
    }
    ArrayProvider provider("name", records);
    for (int i = 0; i < 50; i++){
        shared_ptr<Record>  ptr = provider.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = provider.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    ArrayProviderTest test;
    test.testGenerating50Records();
    test.testGenerating10Records();
}