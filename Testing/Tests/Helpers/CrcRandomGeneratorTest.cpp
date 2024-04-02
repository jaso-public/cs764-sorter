#include "CrcRandomGeneratorTest.h"

void CrcRandomGeneratorTest::testNextWith10Records() {
    SorterConfig cfg;
    cfg.recordCount = 10;
    CrcRandomGenerator generator(cfg);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        assert("Verify checksum was not correct" && generator.verifyCrc(ptr) == true );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
    assert("Verify checksum was not correct" && generator.verifyCrc(ptr) == false );
}

void CrcRandomGeneratorTest::testNextWith50Records() {
    SorterConfig cfg;
    cfg.recordCount = 50;
    CrcRandomGenerator generator(cfg);
    for (int i = 0; i < 50; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
        assert("Verify checksum was not correct" && generator.verifyCrc(ptr) == true );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
    assert("Verify checksum was not correct" && generator.verifyCrc(ptr) == false );
}

int main(){
    CrcRandomGeneratorTest test;
    test.testNextWith10Records();
    test.testNextWith50Records();
}