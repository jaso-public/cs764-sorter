#include <cassert>
#include "src/Generator.h"
#include "src/Provider.h"


//TODO: this gets moved into provider
//TODO: want a tester that automatically makes an input file, tests it, and deletes it
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