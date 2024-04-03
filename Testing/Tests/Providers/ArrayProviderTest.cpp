#include "ArrayProviderTest.h"

void ArrayProviderTest::testGenerating10Records() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 10;
    InOrderGenerator generator(*cfg);
    vector<Record> records;
    for (int i=0; i<10; i++){
        shared_ptr<Record> r = generator.next();
        records.push_back(*r);
    }
    assert("Record size should have been 10" && records.size() == 10 );
    ArrayProvider provider("name", records);
    for (int i = 0; i < 10; i++){
        shared_ptr<Record>  ptr = provider.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = provider.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void ArrayProviderTest::testGenerating50Records() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 50;
    InOrderGenerator generator(*cfg);
    vector<Record> records;
    for (int i=0; i<50; i++){
        shared_ptr<Record>  r = generator.next();
        records.push_back(*r);
    }
    assert("Record size should have been 50" && records.size() == 50 );
    ArrayProvider provider("name", records);
    for (int i = 0; i < 50; i++){
        shared_ptr<Record>  ptr = provider.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = provider.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    ArrayProviderTest test;
    test.testGenerating50Records();
    test.testGenerating10Records();
}