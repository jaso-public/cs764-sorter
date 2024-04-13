#include <iostream>
#include <cassert>

#include "Record.h"
#include "src/Generator.h"
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

    assert("Duplicate was not detected" && ptr1->compareTo(ptr2) == 0);

    // put some different data in the ptr2 record.
    data3[0] = 9;
    auto ptr3 = make_shared<Record>(data3);
    assert("None duplicate was not detected" && ptr1->compareTo(ptr3) != 0);
}

void testCompare() {
    int recordSize = Record::getRecordSize();
    auto data1 = std::make_unique<uint8_t[]>(recordSize);
    auto data2 = std::make_unique<uint8_t[]>(recordSize);

    auto ptr1 = make_shared<Record>(data1);
    auto ptr2 = make_shared<Record>(data2);

    Record::resetCompareCount();
    assert("Compare count was wrong" && Record::getCompareCount() == 0);
    assert("Compare did not work" && ptr1->compareTo(ptr2) == 0);
    assert("Compare count was wrong" &&Record::getCompareCount() == 1);
    Record::resetCompareCount();
    assert("Compare count was wrong" && Record::getCompareCount() == 0);
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
    return; // TODO make this test work

    int recordCount = 10;
    auto generator = make_shared<RandomProvider>(recordCount, true);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator->next();
        assert("Next should have existed" && ptr != nullptr );
        assert("Verify checksum was not correct" && isCrcValid(ptr) == true );
    }
    shared_ptr<Record> ptr = generator->next();
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