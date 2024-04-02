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

int main(){
    RecordTest test;
    test.testNoParameterConstructor();
    test.testDataParameterConstructor();
}