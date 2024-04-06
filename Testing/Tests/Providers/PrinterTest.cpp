
#include "assert.h"

#include "test/helpers/Generators.h"
#include "test/helpers/ArrayProvider.h"


void testCount10() {
    auto records = generateInOrder(20);
    ArrayProvider generator("name", records);
    Printer printer(&generator, "this is a test message");
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = printer.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = printer.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testCount50() {
    auto records = generateInOrder(50);
    ArrayProvider generator("name", records);
    Printer printer(&generator, "this is a test message");
    for (int i = 0; i < 50; i++){
        shared_ptr<Record>  ptr = printer.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = printer.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}


int main(){
    testCount10();
    testCount50();
}