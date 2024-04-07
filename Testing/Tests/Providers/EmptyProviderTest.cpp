#include <cassert>
#include "test/helpers/Generator.h"
#include "src/Provider.h"

void testNext() {
    shared_ptr<Provider> generator = make_shared<EmptyProvider>();
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator->next();
        assert("Next should be nullptr" && ptr == nullptr );
    }
}

int main(){
    testNext();
}