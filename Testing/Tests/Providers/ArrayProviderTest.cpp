#include "cassert"
#include "test/helpers/Generator.h"

void testGenerating10Records() {
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

void testGenerating50Records() {
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
    testGenerating50Records();
    testGenerating10Records();
}