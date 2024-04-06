#include "RecordTest.h"


void RecordTest::testNoParameterConstructor() {
    auto ptr = make_shared<Record>();
}

void RecordTest::testDataParameterConstructor() {
    int recordSize = Record::getRecordSize();
    uint8_t data[recordSize];
    for(int i=0 ; i<recordSize ; i++) data[i] = i;

    auto ptr = make_shared<Record>(&data[0]);
}

void RecordTest::testIsDuplicate() {
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

void RecordTest::testCompare() {
    uint8_t* data = new uint8_t[Record::getRecordSize()];
    auto ptr1 = make_shared<Record>(&data[0]);
    auto ptr2 = make_shared<Record>(&data[0]);

    assert("Compare count was wrong" && ptr1->getCompareCount() == 0);
    assert("Compare did not work" && ptr1->compareTo(ptr2) == 0);
    assert("Compare count was wrong" && ptr1->getCompareCount() == 1);
    ptr1->resetCompareCount();
    assert("Compare count was wrong" && ptr1->getCompareCount() == 0);
}

void RecordTest::testCheckSum() {
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

int main(){
    RecordTest test;
    test.testNoParameterConstructor();
    test.testDataParameterConstructor();
    test.testIsDuplicate();
    test.testCompare();
    test.testCheckSum();
}