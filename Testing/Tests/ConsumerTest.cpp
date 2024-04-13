#include "src/Generator.h"
#include "src/Consumer.h"
#include "cassert"


void testConsume() {
    string inputFileName = "input.txt";
    uint32_t hddReadSize = 256 * 1024;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    auto consumer = make_shared<NoopConsumer>(provider);
    consumer->consume();
    shared_ptr<Record> ptr = provider->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    testConsume();
}