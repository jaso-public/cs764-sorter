#include <cassert>
#include "Record.h"
#include "Provider.h"
#include "src/Generator.h"
#include <string>
#include "src/Witness.h"
#include "test/helpers/TreeSorter.h"
#include "src/Consumer.h"


void testTenRecords() {
    auto source = make_shared<RandomProvider>(10);

    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = source->next();
        assert("Next should have existed" && ptr != nullptr );
    }

    shared_ptr<Record> ptr = source->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


void
testSingleProvider() {
    shared_ptr<SingleProvider> single = make_shared<SingleProvider>();
    shared_ptr<Record> record = single->next();
    assert("Next should not have given a null pointer" && record == nullptr );

    int recordSize = 10;
    unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(recordSize);

    single->reset(make_shared<Record>(data));
    record = single->next();
    assert("Next should not have given a null pointer" && record != nullptr );
    assert("Next should have given a null pointer" && single->next() == nullptr );
}

void testMemoryProvider() {
    int recordCount = 10;
    auto records = generateRandom(recordCount);
    uint8_t buffer [1000];
    long offset = 0;
    for (int i = 0; i < recordCount; i++) {
        shared_ptr<Record> ptr = records[i];
        ptr->store(buffer + offset);
        offset += Record::getRecordSize();
    }

    auto memoryProvider = make_shared<MemoryProvider>(buffer, recordCount);
    for(int i=0 ; i<recordCount ; i++) {
        shared_ptr<Record> existing = records[i];
        shared_ptr<Record> retrieved = memoryProvider->next();
        assert("different" && existing->compareTo(retrieved) ==0);
     }
}

void testEmptyProvider() {
    shared_ptr<Provider> generator = make_shared<EmptyProvider>();
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator->next();
        assert("Next should be nullptr" && ptr == nullptr );
    }
}

void testRandomProvider(int recordCount){
    auto generator = make_shared<RandomProvider>(recordCount);
    for (int i = 0; i < recordCount; i++){
        shared_ptr<Record>  ptr = generator->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testNextWithDeviceProvider(string inputFileName, int recordCount, int recordSize) {
    Record::staticInitialize(recordSize);
    uint32_t hddReadSize = 256 * 1024;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);

    for (int i = 0; i < recordCount; i++){
        shared_ptr<Record> ptr = provider->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = provider->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testInputChainWithDeviceProvider(string inputFileName, int recordCount, int recordSize) {
    Record::staticInitialize(recordSize);
    uint32_t hddReadSize = 256 * 1024;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    shared_ptr<Witness>  lower = make_shared<Witness>(provider);
    shared_ptr<Witness>  upper = make_shared<Witness>(lower);
    auto consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    assert("The count of the lower witness did not equal the count of the upper but should have" && lower->getCount() == upper->getCount());
    assert("The count of the upper witness was wrong" && recordCount == upper->getCount());
    assert("The sorting of the witnesses should have been the same" && upper->isSorted() == lower->isSorted());
}

void testDropOneWithDeviceProvider(string inputFileName, int recordCount, int recordSize) {
    Record::staticInitialize(recordSize);
    uint32_t hddReadSize = 256 * 1024;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    shared_ptr<Witness>  lower = make_shared<Witness>(provider);
    shared_ptr<DropFirst> dropper = make_shared<DropFirst>(lower);
    shared_ptr<Witness>  upper = make_shared<Witness>(dropper);
    auto consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    assert("The count of the lower witness did not equal the count of the upper but should have" && upper->getCount() == lower->getCount() - 1);
    assert("The count of the upper witness was wrong" && recordCount -1 == upper->getCount());
    assert("The sorting of the witnesses should have been the same" && upper->isSorted() == lower->isSorted());
}

void testTreeSorterWithDeviceProvider(string inputFileName, int recordCount, int recordSize) {
    Record::staticInitialize(recordSize);
    uint32_t hddReadSize = 256 * 1024;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    shared_ptr<Witness>  lower = make_shared<Witness>(provider);
    shared_ptr<DropFirst> dropper = make_shared<DropFirst>(lower);
    shared_ptr<TreeSorter> sorter = make_shared<TreeSorter>(dropper);
    shared_ptr<Witness>  upper = make_shared<Witness>(sorter);
    auto consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    // just ensures consumer will return null pointer (consumes everything)
    shared_ptr<Record> ptr = provider->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
    assert("The count of the lower witness did not equal the count of the upper but should have" && lower->getCount()-1 == upper->getCount());
    assert("The count of the upper witness was wrong" && recordCount-1 == upper->getCount());
    assert("The sorting of the witnesses should have been the same" && upper->isSorted() != lower->isSorted());
}

int main(){
    testTenRecords();
    testSingleProvider();
    testMemoryProvider();
    testEmptyProvider();
    testRandomProvider(10);
    testRandomProvider(50);
    testNextWithDeviceProvider("../ExampleFiles/input_table",20, 1024);
    testInputChainWithDeviceProvider("../ExampleFiles/input_table",20, 1024);
    testDropOneWithDeviceProvider("../ExampleFiles/input_table",20, 1024);
    testTreeSorterWithDeviceProvider("../ExampleFiles/input_table",20, 1024);
}