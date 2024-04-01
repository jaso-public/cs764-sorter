#include "SingleProviderTest.h"

void SingleProviderTest::testNext() {
    SingleProvider single;
    Record* record = single.next();
    assert("Next should not have given a null pointer" && record != nullptr );
    assert("Next should have given a null pointer" && single.next() == nullptr );
    single.reset(record);
    record = single.next();
    assert("Next should not have given a null pointer" && record != nullptr );
    assert("Next should have given a null pointer" && single.next() == nullptr );
}

int main(){
    SingleProviderTest test;
    test.testNext();
}