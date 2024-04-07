#include <cassert>
#include "Provider.h"
#include "src/Witness.h"
#include "Testing/SorterHelpers/TreeSorter.h"
#include "test/helpers/Generator.h"

void testCount10() {
    auto records = generateRandom(10);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness>  lower = make_shared<Witness>(source);
    shared_ptr<TreeSorter> sorter = make_shared<TreeSorter>(lower);

    shared_ptr<Record> prevRecordPtr = nullptr;
    Record prevRecord;
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = sorter->next();
        Record currentRecord = *ptr;
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecordPtr != nullptr){
            assert("The keys should have been sorted but were not" && currentRecord.compareTo(prevRecordPtr) >= 0 );
        }
        prevRecordPtr = ptr;
    }
    shared_ptr<Record> ptr = sorter->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testCount50() {
    auto records = generateRandom(50);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness>  lower = make_shared<Witness>(source);
    shared_ptr<TreeSorter> sorter = make_shared<TreeSorter>(lower);

    shared_ptr<Record> prevRecordPtr = nullptr;
    Record prevRecord;
    for (int i = 0; i < 50; i++){
        shared_ptr<Record> ptr = sorter->next();
        Record currentRecord = *ptr;
        assert("Next should have existed" && ptr != nullptr );
        if (prevRecordPtr != nullptr){
            assert("The keys should have been sorted but were not" && currentRecord.compareTo(prevRecordPtr) >= 0 );
        }
        prevRecordPtr = ptr;
    }
    shared_ptr<Record> ptr = sorter->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    testCount10();
    testCount50();
}