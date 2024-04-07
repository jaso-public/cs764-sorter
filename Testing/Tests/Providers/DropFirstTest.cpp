#include <cassert>
#include "test/helpers/Generator.h"
#include "Provider.h"
#include "src/Witness.h"
#include "Testing/TestProviders/DropFirst.h"

void testDropWithCount10() {
    auto records = generateInOrder(10);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness>  lower = make_shared<Witness>(source);
    shared_ptr<DropFirst>  dropper = make_shared<DropFirst>(lower);
    for (int i = 0; i < 9; i++){
        shared_ptr<Record> ptr = dropper->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = dropper->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testDropWithCount20() {
    auto records = generateInOrder(20);
    shared_ptr<Provider> source = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness>  lower = make_shared<Witness>(source);
    shared_ptr<DropFirst>  dropper = make_shared<DropFirst>(lower);
    for (int i = 0; i < 19; i++){
        shared_ptr<Record>  ptr = dropper->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = dropper->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    testDropWithCount10();
    testDropWithCount20();
}