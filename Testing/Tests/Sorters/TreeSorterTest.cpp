#include <cassert>

void testCount10() {
    auto records = generateRandom(10);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    TreeSorter sorter(&lower);
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

void testCount50() {
    auto records = generateRandom(50);
    ArrayProvider provider("name", records);
    Witness lower(&provider);
    TreeSorter sorter(&lower);
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
    testCount10();
    testCount50();
}