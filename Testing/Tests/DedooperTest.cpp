#include "DedooperTest.h"
void DedooperTest::testDuplicateRemoval10() {
    InOrderGenerator generator(10, 100, 8);
    Record* prevRecord = nullptr;
    for (int i = 0; i < 10; i++){
        Record* ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecord){
            Record r = *ptr;
            assert("Duplicate record was found" && r.compareTo(prevRecord) == 0);
        }
        prevRecord = ptr;
    }
    Record* ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void DedooperTest::testDuplicateRemoval100() {
    InOrderGenerator generator(100, 100, 8);
    Record* prevRecord = nullptr;
    for (int i = 0; i < 100; i++){
        Record* ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecord){
            Record r = *ptr;
            assert("Duplicate record was found" && r.compareTo(prevRecord) == 0);
        }
        prevRecord = ptr;
    }
    Record* ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    DedooperTest test;
    test.testDuplicateRemoval10();
    test.testDuplicateRemoval100();
}