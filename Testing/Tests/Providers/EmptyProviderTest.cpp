#include <cassert>

void testNext() {
    EmptyProvider generator;
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should be nullptr" && ptr == nullptr );
    }
}

int main(){
    testNext();
}