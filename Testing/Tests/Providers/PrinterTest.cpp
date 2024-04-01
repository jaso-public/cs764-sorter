#include "PrinterTest.h"

void PrinterTest::testCount10() {
    InOrderGenerator generator(10, 100, 8);
    Printer printer(&generator, "this is a test message");
    for (int i = 0; i < 10; i++){
        Record* ptr = printer.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    Record* ptr = printer.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void PrinterTest::testCount50() {
    InOrderGenerator generator(50, 100, 8);
    Printer printer(&generator, "this is a test message");
    for (int i = 0; i < 50; i++){
        Record* ptr = printer.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    Record* ptr = printer.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    PrinterTest test;
    test.testCount10();
    test.testCount50();
}