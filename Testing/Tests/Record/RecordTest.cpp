#include "RecordTest.h"


void RecordTest::testNoParameterConstructor() {
    SorterConfig cfg;
    Record::staticInitialize(cfg.recordSize, cfg.keyOffset, cfg.keySize);
    shared_ptr<Record> ptr(new Record);
}

void RecordTest::testDataParameterConstructor() {
    SorterConfig cfg;
    uint8_t* data = new uint8_t[cfg.recordSize];
    Record::staticInitialize(cfg.recordSize, cfg.keyOffset, cfg.keySize);
    shared_ptr<Record> ptr(new Record(data));
}

void RecordTest::testIsDuplicate() {
    SorterConfig cfg;
    cfg.recordSize = 3;
    uint8_t* data = new uint8_t[cfg.recordSize];
    Record::staticInitialize(cfg.recordSize, cfg.keyOffset, cfg.keySize);
    shared_ptr<Record> ptr1(new Record(data));
    shared_ptr<Record> ptr2(new Record(data));
    for (int i = 0; i < 3; i++){
        ptr1->data[i] = i;
        ptr2->data[i] = i;
    }
    assert("Duplicate was not detected" && ptr1->isDuplicate(*ptr2) == true);
    ptr2->data[0] = 5;
    assert("None duplicate was not detected" && ptr1->isDuplicate(*ptr2) == false);
}

void RecordTest::testCompare() {
    SorterConfig cfg;
    cfg.recordSize = 3;
    uint8_t* data = new uint8_t[cfg.recordSize];
    Record::staticInitialize(cfg.recordSize, cfg.keyOffset, cfg.keySize);
    shared_ptr<Record> ptr1(new Record(data));
    shared_ptr<Record> ptr2(new Record(data));
    assert("Compare count was wrong" && ptr1->getCompareCount() == 0);
    assert("Compare did not work" && ptr1->compareTo(*ptr2) == 0);
    assert("Compare count was wrong" && ptr1->getCompareCount() == 1);
    ptr1->resetCompareCount();
    assert("Compare count was wrong" && ptr1->getCompareCount() == 0);
}

void RecordTest::testCheckSum() {
    SorterConfig cfg;
    uint8_t* data = new uint8_t[cfg.recordSize];
    Record::staticInitialize(cfg.recordSize, cfg.keyOffset, cfg.keySize);
    shared_ptr<Record> ptr1(new Record(data));
    shared_ptr<Record> ptr2(new Record(data));
    for (int i = 0; i < 16; i++){
        ptr1->data[i] = i;
        ptr2->data[i] = i;
    }
    uint64_t checksum1 = ptr1->checksum();
    uint64_t checksum2 = ptr2->checksum();
    assert("Checksums should have been the same but were not" && checksum1 == checksum2);
    ptr2->data[1] = 5;
    checksum2 = ptr2->checksum();
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