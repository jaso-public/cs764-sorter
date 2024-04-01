#include "ConsumerTest.h"

void ConsumerTest::testConsume() {
    SorterConfig cfg;
    cfg.recordCount = 10;
    InOrderGenerator generator(cfg);
    Consumer consume(&generator);
    consume.consume();
    shared_ptr<Record> ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    ConsumerTest test;
    test.testConsume();
}