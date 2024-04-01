#include "EmptyProviderTest.h"

void EmptyProviderTest::testNext() {
    EmptyProvider generator;
    for (int i = 0; i < 10; i++){
        Record* ptr = generator.next();
        assert("Next should be nullptr" && ptr == nullptr );
    }
}

int main(){
    EmptyProviderTest test;
    test.testNext();
}