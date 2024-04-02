#include "DedooperTest.h"
void DedooperTest::testDuplicateRemoval10() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 10;
    InOrderGenerator generator(*cfg);
    shared_ptr<Record> prevRecord = nullptr;
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecord){
            Record r = *ptr;
            assert("Duplicate record was found" && r.compareTo(*prevRecord) == 0);
        }
        prevRecord = ptr;
    }
    shared_ptr<Record> ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void DedooperTest::testDuplicateRemoval100() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 100;
    InOrderGenerator generator(*cfg);
    shared_ptr<Record> prevRecord = nullptr;
    for (int i = 0; i < 100; i++){
        shared_ptr<Record>  ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecord){
            Record r = *ptr;
            assert("Duplicate record was found" && r.compareTo(*prevRecord) == 0);
        }
        prevRecord = ptr;
    }
    shared_ptr<Record> ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    DedooperTest test;
    test.testDuplicateRemoval10();
    test.testDuplicateRemoval100();
}