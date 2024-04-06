#include "CrcRandomGeneratorTest.h"

void CrcRandomGeneratorTest::testNextWith10Records() {
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

void CrcRandomGeneratorTest::testNextWith50Records() {
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
    CrcRandomGeneratorTest test;
    test.testNextWith10Records();
    test.testNextWith50Records();
}