#include "RecordProviderTest.h"

void RecordProviderTest::testNext() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 20;
    cfg->recordSize = 1024;
    string file = "../ExampleFiles/input_table";
    RecordProvider recordProvider(*cfg, file);
    recordProvider.next();
}

int main(){
    RecordProviderTest test;
    test.testNext();
}