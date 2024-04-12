#include <cassert>
#include "src/Generator.h"
#include "Provider.h"

void testCount10() {
    auto records = generateRandom(10);
    ArrayProvider generator("name", records);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testCount50() {
    auto records = generateRandom(50);
    ArrayProvider generator("name", records);
    for (int i = 0; i < 50; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    testCount10();
    testCount50();
}