#include <iostream>
#include <cassert>

#include "Record.h"
#include "test/helpers/Generators.h"
#include "Provider.h"
#include "assert.h"


void testNoParameterConstructor() {
    auto ptr = make_shared<Record>();
}

void testDataParameterConstructor() {
    int recordSize = Record::getRecordSize();
    uint8_t data[recordSize];
    for(int i=0 ; i<recordSize ; i++) data[i] = i;

    auto ptr = make_shared<Record>(&data[0]);
}

void testIsDuplicate() {
    int recordSize = Record::getRecordSize();
    uint8_t data[recordSize];
    for(int i = 0; i < recordSize; i++) {
        data[i] = i;
    }

    auto ptr1 = make_shared<Record>(&data[0]);
    auto ptr2 = make_shared<Record>(&data[0]);

    assert("Duplicate was not detected" && ptr1->isDuplicate(ptr2) == true);

    // put some different data in the ptr2 record.
    data[0] = 9;
    ptr2 = make_shared<Record>(&data[0]);
    assert("None duplicate was not detected" && ptr1->isDuplicate(ptr2) == false);
}

void testCompare() {
    uint8_t* data = new uint8_t[Record::getRecordSize()];
    auto ptr1 = make_shared<Record>(&data[0]);
    auto ptr2 = make_shared<Record>(&data[0]);

    assert("Compare count was wrong" && ptr1->getCompareCount() == 0);
    assert("Compare did not work" && ptr1->compareTo(ptr2) == 0);
    assert("Compare count was wrong" && ptr1->getCompareCount() == 1);
    ptr1->resetCompareCount();
    assert("Compare count was wrong" && ptr1->getCompareCount() == 0);
}

void testCheckSum() {
    int recordSize = Record::getRecordSize();
    uint8_t data[recordSize];
    for(int i = 0; i < recordSize; i++) {
        data[i] = i;
    }

    auto ptr1 = make_shared<Record>(&data[0]);
    auto ptr2 = make_shared<Record>(&data[0]);

    uint64_t checksum1 = ptr1->checksum();
    uint64_t checksum2 = ptr2->checksum();
    assert("Checksums should have been the same but were not" && checksum1 == checksum2);
    data[1] = 5;
    ptr2 = make_shared<Record>(&data[0]);
    assert("Checksums should have been different but were not" && checksum1 == checksum2);
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

void testNextWith50RecordsWithCrc() {
    auto records = generateRandomWithCrc(50);
    ArrayProvider generator("name", records);
    for (int i = 0; i < 50; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        assert("Verify checksum was not correct" && isCrcValid(ptr) == true );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
    assert("Verify checksum was not correct" && isCrcValid(ptr) == false );
}

int main(){
    testNoParameterConstructor();
    testDataParameterConstructor();
    testIsDuplicate();
    testCompare();
    testCheckSum();
    testNextWith10RecordsWithCrc();
    testNextWith50RecordsWithCrc();
}