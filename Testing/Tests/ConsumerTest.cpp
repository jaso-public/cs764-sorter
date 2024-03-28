#include "ConsumerTest.h"

void ConsumerTest::testConsume() {
    InOrderGenerator generator(10, 100, 8);
    Consumer consume(&generator);
    consume.consume();
    Record* ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    ConsumerTest test;
    test.testConsume();
}