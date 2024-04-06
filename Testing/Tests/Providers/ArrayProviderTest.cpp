#include "ArrayProviderTest.h"

void ArrayProviderTest::testGenerating10Records() {
    auto records = generateInOrder(10);
    assert("Record size should have been 10" && records.size() == 10 );
    ArrayProvider provider("name", records);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = provider.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = provider.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void ArrayProviderTest::testGenerating50Records() {
    auto records = generateInOrder(50);
    assert("Record size should have been 50" && records.size() == 50 );
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