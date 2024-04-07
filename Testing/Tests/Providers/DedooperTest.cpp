#include <cassert>
#include "test/helpers/Generator.h"
#include "Provider.h"


void testDuplicateRemoval10() {
    auto records = generateInOrder(10);
    shared_ptr<Record> prevRecord = nullptr;
    ArrayProvider generator("name", records);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecord){
            Record r = *ptr;
            assert("Duplicate record was found" && r.compareTo(prevRecord) == 0);
        }
        prevRecord = ptr;
    }
    shared_ptr<Record> ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testDuplicateRemoval100() {
    auto records = generateInOrder(100);
    ArrayProvider generator("name", records);
    shared_ptr<Record> prevRecord = nullptr;
    for (int i = 0; i < 100; i++){
        shared_ptr<Record>  ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecord){
            Record r = *ptr;
            assert("Duplicate record was found" && r.compareTo(prevRecord) == 0);
        }
        prevRecord = ptr;
    }
    shared_ptr<Record> ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    testDuplicateRemoval10();
    testDuplicateRemoval100();
}