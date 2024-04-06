#include "ConsumerTest.h"

void ConsumerTest::testConsume() {
    auto records = generateRandom(10);
    ArrayProvider provider("name", records);
    Consumer consume(&provider);
    consume.consume();
    shared_ptr<Record> ptr = provider.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    ConsumerTest test;
    test.testConsume();
}