#include "PrinterTest.h"

void PrinterTest::testCount10() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 10;
    InOrderGenerator generator(*cfg);
    Printer printer(&generator, "this is a test message");
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = printer.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = printer.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void PrinterTest::testCount50() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 50;
    InOrderGenerator generator(*cfg);
    Printer printer(&generator, "this is a test message");
    for (int i = 0; i < 50; i++){
        shared_ptr<Record>  ptr = printer.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = printer.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    PrinterTest test;
    test.testCount10();
    test.testCount50();
}