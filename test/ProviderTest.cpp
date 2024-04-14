#include <iostream>
#include <cassert>

#include "Record.h"
#include "Provider.h"
#include "src/Generator.h"

//TODO: want a tester that automatically makes an input file, tests it, and deletes it
void testTenRecords() {
    auto source = make_shared<RandomProvider>(10);

    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = source->next();
        assert("Next should have existed" && ptr != nullptr );
    }

    shared_ptr<Record> ptr = source->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


void
testSingleProvider() {
    shared_ptr<SingleProvider> single = make_shared<SingleProvider>();
    shared_ptr<Record> record = single->next();
    assert("Next should not have given a null pointer" && record == nullptr );

    int recordSize = 10;
    unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(recordSize);

    single->reset(make_shared<Record>(data));
    record = single->next();
    assert("Next should not have given a null pointer" && record != nullptr );
    assert("Next should have given a null pointer" && single->next() == nullptr );
}

void
testMemoryProvider() {
    int recordCount = 10;
    auto records = generateRandom(recordCount);
    uint8_t buffer [1000];
    long offset = 0;
    for (int i = 0; i < recordCount; i++) {
        shared_ptr<Record> ptr = records[i];
        ptr->store(buffer + offset);
        offset += Record::getRecordSize();
    }

    auto memoryProvider = make_shared<MemoryProvider>(buffer, recordCount);
    for(int i=0 ; i<recordCount ; i++) {
        shared_ptr<Record> existing = records[i];
        shared_ptr<Record> retrieved = memoryProvider->next();
        assert("different" && existing->compareTo(retrieved) ==0);
     }
}

void testEmptyProvider() {
    shared_ptr<Provider> generator = make_shared<EmptyProvider>();
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator->next();
        assert("Next should be nullptr" && ptr == nullptr );
    }
}

int main(){
    testTenRecords();
    testSingleProvider();
    testMemoryProvider();
    testEmptyProvider();

}