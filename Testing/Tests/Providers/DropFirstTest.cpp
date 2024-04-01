#include "DropFirstTest.h"

void DropFirstTest::testDropWithCount10() {
    SorterConfig cfg;
    cfg.recordCount = 10;
    InOrderGenerator i(cfg);
    Witness lower(&i);
    DropFirst dropper(&lower);
    for (int i = 0; i < 9; i++){
        shared_ptr<Record> ptr = dropper.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = dropper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void DropFirstTest::testDropWithCount20() {
    SorterConfig cfg;
    cfg.recordCount = 20;
    InOrderGenerator i(cfg);
    Witness lower(&i);
    DropFirst dropper(&lower);
    for (int i = 0; i < 19; i++){
        shared_ptr<Record>  ptr = dropper.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = dropper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    DropFirstTest test;
    test.testDropWithCount10();
    test.testDropWithCount20();
}