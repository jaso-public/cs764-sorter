#include <iostream>
#include <cassert>

#include "Record.h"
#include "test/helpers/Generators.h"
#include "test/helpers/ArrayProvider.h"

void testTenRecords() {
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", generateInOrder(10));

    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = source->next();
        ptr->dump();
        assert("Next should have existed" && ptr != nullptr );
    }

    shared_ptr<Record> ptr = source->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    testTenRecords();
}