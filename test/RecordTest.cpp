#include <iostream>
#include <cassert>

#include "Record.h"
#include "test/helpers/Generator.h"
#include "Provider.h"


void testDataParameterConstructor() {
    int recordSize = Record::getRecordSize();
    auto data1 = std::make_unique<uint8_t[]>(recordSize);
    auto data2 = std::make_unique<uint8_t[]>(recordSize);
    auto data3 = std::make_unique<uint8_t[]>(recordSize);

    for(int i = 0; i < recordSize; i++) {
        data1[i] = i;
        data2[i] = i;
        data3[i] = i;
    }

    auto ptr = make_shared<Record>(data1);
}

void testIsDuplicate() {
    int recordSize = Record::getRecordSize();
    auto data1 = std::make_unique<uint8_t[]>(recordSize);
    auto data2 = std::make_unique<uint8_t[]>(recordSize);
    auto data3 = std::make_unique<uint8_t[]>(recordSize);

    for(int i = 0; i < recordSize; i++) {
        data1[i] = i;
        data2[i] = i;
        data3[i] = i;
    }

    auto ptr1 = make_shared<Record>(data1);
    auto ptr2 = make_shared<Record>(data2);

    assert("Duplicate was not detected" && ptr1->isDuplicate(ptr2) == true);

    // put some different data in the ptr2 record.
    data3[0] = 9;
    auto ptr3 = make_shared<Record>(data3);
    assert("None duplicate was not detected" && ptr1->isDuplicate(ptr3) == false);
}

void testCompare() {
    int recordSize = Record::getRecordSize();
    auto data1 = std::make_unique<uint8_t[]>(recordSize);
    auto data2 = std::make_unique<uint8_t[]>(recordSize);

    auto ptr1 = make_shared<Record>(data1);
    auto ptr2 = make_shared<Record>(data2);

    assert("Compare count was wrong" && ptr1->getCompareCount() == 0);
    assert("Compare did not work" && ptr1->compareTo(ptr2) == 0);
    assert("Compare count was wrong" && ptr1->getCompareCount() == 1);
    ptr1->resetCompareCount();
    assert("Compare count was wrong" && ptr1->getCompareCount() == 0);
}

void testCheckSum() {
    int recordSize = Record::getRecordSize();
    auto data1 = std::make_unique<uint8_t[]>(recordSize);
    auto data2 = std::make_unique<uint8_t[]>(recordSize);
    auto data3 = std::make_unique<uint8_t[]>(recordSize);

    for(int i = 0; i < recordSize; i++) {
        data1[i] = i;
        data2[i] = i;
        data3[i] = i;
    }

    auto ptr1 = make_shared<Record>(data1);
    auto ptr2 = make_shared<Record>(data2);

    uint64_t checksum1 = ptr1->checksum();
    uint64_t checksum2 = ptr2->checksum();
    assert("Checksums should have been the same but were not" && checksum1 == checksum2);
    data3[1] = 5;
    auto ptr3 = make_shared<Record>(data3);
    uint64_t checksum3 = ptr3->checksum();

    assert("Checksums should have been different but were not" && checksum1 != checksum3);
}

void testNextWith10RecordsWithCrc() {
    auto records = generateRandomWithCrc(10);

    ArrayProvider generator("name", records);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        assert("Verify checksum was not correct" && isCrcValid(ptr) == true );
    }
    shared_ptr<Record> ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
    assert("Verify checksum was not correct" && isCrcValid(ptr) == false );
}

int main(){
    testDataParameterConstructor();
    testIsDuplicate();
    testCompare();
    testCheckSum();
    testNextWith10RecordsWithCrc();
 }