#include "TreeSorterTest.h"

void TreeSorterTest::testCount10() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 10;
    RandomGenerator r(*cfg);
    Witness lower(&r);
    TreeSorter sorter(&r);
    shared_ptr<Record> prevRecordPtr = nullptr;
    Record prevRecord;
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = sorter.next();
        Record currentRecord = *ptr;
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecordPtr != nullptr){
            assert("The keys should have been sorted but were not" && currentRecord.compareTo(*prevRecordPtr) >= 0 );
        }
        prevRecordPtr = ptr;
    }
    shared_ptr<Record> ptr = sorter.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void TreeSorterTest::testCount50() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 50;
    RandomGenerator r(*cfg);
    Witness lower(&r);
    TreeSorter sorter(&r);
    shared_ptr<Record> prevRecordPtr = nullptr;
    Record prevRecord;
    for (int i = 0; i < 50; i++){
        shared_ptr<Record> ptr = sorter.next();
        Record currentRecord = *ptr;
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecordPtr != nullptr){
            assert("The keys should have been sorted but were not" && currentRecord.compareTo(*prevRecordPtr) >= 0 );
        }
        prevRecordPtr = ptr;
    }
    shared_ptr<Record> ptr = sorter.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    TreeSorterTest test;
    test.testCount10();
    test.testCount50();
}