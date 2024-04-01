#include "DropFirstTest.h"

void DropFirstTest::testDropWithCount10() {
    InOrderGenerator i(10, 100, 8, 8);
    Witness lower(&i);
    DropFirst dropper(&lower);
    for (int i = 0; i < 9; i++){
        Record* ptr = dropper.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    Record* ptr = dropper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void DropFirstTest::testDropWithCount20() {
    InOrderGenerator i(20, 100, 88);
    Witness lower(&i);
    DropFirst dropper(&lower);
    for (int i = 0; i < 19; i++){
        Record* ptr = dropper.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    Record* ptr = dropper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    DropFirstTest test;
    test.testDropWithCount10();
    test.testDropWithCount20();
}