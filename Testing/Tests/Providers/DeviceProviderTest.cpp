#include <cassert>
#include <string>
#include "Provider.h"
#include "src/Witness.h"
#include "test/helpers/TreeSorter.h"
#include "test/helpers/NoopSorter.h"
#include "Testing/TestProviders/DropFirst.h"
#include "src/Consumer.h"


void testNext() {
    string inputFileName = "../ExampleFiles/input_table";
    uint32_t hddReadSize = 256 * 1024;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    provider->next();
}

void testInputRecord() {
    string inputFileName = "../ExampleFiles/input_table";
    uint32_t hddReadSize = 256 * 1024;
    int recordCount = 20;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);

    for (int i = 0; i < recordCount; i++){
        shared_ptr<Record> ptr = provider->next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = provider->next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testInputChain() {
    string inputFileName = "../ExampleFiles/input_table";
    uint32_t hddReadSize = 256 * 1024;
    int recordCount = 20;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    shared_ptr<Witness>  lower = make_shared<Witness>(provider);
    shared_ptr<NoopSorter> sorter = make_shared<NoopSorter>(lower);
    shared_ptr<Witness>  upper = make_shared<Witness>(sorter);
    auto consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    assert("The count of the lower witness did not equal the count of the upper but should have" && lower->getCount() == upper->getCount());
    assert("The count of the upper witness was wrong" && recordCount == upper->getCount());
    assert("The sorting of the witnesses should have been the same" && upper->isSorted() == lower->isSorted());
}

void testDropOne() {
    string inputFileName = "../ExampleFiles/input_table";
    uint32_t hddReadSize = 256 * 1024;
    int recordCount = 20;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    shared_ptr<Witness>  lower = make_shared<Witness>(provider);
    shared_ptr<DropFirst> dropper = make_shared<DropFirst>(lower);
    shared_ptr<NoopSorter> sorter = make_shared<NoopSorter>(dropper);
    shared_ptr<Witness>  upper = make_shared<Witness>(sorter);
    auto consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();


    assert("The count of the lower witness did not equal the count of the upper but should have" && lower->getCount() == upper->getCount());
    assert("The count of the upper witness was wrong" && recordCount == upper->getCount());
    assert("The sorting of the witnesses should have been the same" && upper->isSorted() == lower->isSorted());
}

void testTreeSorter() {
    string inputFileName = "../ExampleFiles/input_table";
    uint32_t hddReadSize = 256 * 1024;
    int recordCount = 20;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    shared_ptr<Witness>  lower = make_shared<Witness>(provider);
    shared_ptr<DropFirst> dropper = make_shared<DropFirst>(lower);
    shared_ptr<TreeSorter> sorter = make_shared<TreeSorter>(dropper);
    shared_ptr<Witness>  upper = make_shared<Witness>(sorter);
    auto consumer = make_shared<NoopConsumer>(upper);
    consumer->consume();

    assert("The count of the lower witness did not equal the count of the upper but should have" && lower->getCount() == upper->getCount());
    assert("The count of the upper witness was wrong" && recordCount == upper->getCount());
    assert("The sorting of the witnesses should have been the same" && upper->isSorted() == lower->isSorted());
}

int main(){
    testNext();
    testInputRecord();
    testInputChain();
    testDropOne();
    testTreeSorter();
}