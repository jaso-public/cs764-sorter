#include <cassert>
#include "src/Generator.h"
#include "Provider.h"

void testRandomGenerator(int recordCount){
    auto generator = make_shared<RandomProvider>(recordCount);
    for (int i = 0; i < recordCount; i++){
        shared_ptr<Record>  ptr = generator->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    testRandomGenerator(10);
    testRandomGenerator(50);
}