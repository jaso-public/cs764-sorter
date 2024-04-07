#include <iostream>
#include <cassert>

#include "Record.h"
#include "Provider.h"
#include "test/helpers/Generators.h"

void testTenRecords() {
    auto records = generateInOrder(10);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);

    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = source->next();
        ptr->dump();
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


int main(){
    testTenRecords();
    testSingleProvider();
}