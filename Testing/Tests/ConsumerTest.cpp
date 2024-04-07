#include "test/helpers/Generator.h"
#include "test/helpers/Consumer.h"
#include "cassert"


void testConsume() {
    auto records = generateRandom(10);
    shared_ptr<Provider> provider = make_shared<ArrayProvider>("name", records);
    Consumer consume(provider);
    consume.consume();
    shared_ptr<Record> ptr = provider->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    testConsume();
}