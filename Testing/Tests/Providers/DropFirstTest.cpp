#include <cassert>
#include "src/Generator.h"
#include "Provider.h"
#include "src/Witness.h"
#include "Testing/TestProviders/DropFirst.h"

void testDropFirstWithRandom(int numRecords) {
    auto provider = make_shared<RandomProvider>(numRecords);
    shared_ptr<Witness>  lower = make_shared<Witness>(provider);
    shared_ptr<DropFirst>  dropper = make_shared<DropFirst>(lower);
    for (int i = 0; i < numRecords-1; i++){
        shared_ptr<Record> ptr = dropper->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = dropper->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    testDropFirstWithRandom(10);
    testDropFirstWithRandom(50);
}