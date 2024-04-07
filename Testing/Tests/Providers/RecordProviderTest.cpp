#include <cassert>
#include <string>
#include "test/helpers/Generator.h"
#include "Provider.h"
#include "src/Witness.h"


void testNext() {
    string file = "../ExampleFiles/input_table";
    InputStreamProvider provider(file);
    provider.next();
}

void testInputRecord() {
    string file = "../ExampleFiles/input_table";
    int recordCount = 20;
    InputStreamProvider provider(file);
    for (int i = 0; i <    recordCount; i++){
        shared_ptr<Record> ptr = provider.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = provider.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testTenInOrder() {
    string file = "../ExampleFiles/input_table";
    int recordCount = 20;
    int recordSize = 1024;
    RecordProvider generator(*cfg, file);
    Witness lower(&generator);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    Dedooper dooper(&upper);
    Consumer consumer(&dooper);
    consumer.consume();

    assert("The count of the lower witness did not equal the count of the upper but should have" && lower.getCount() == upper.getCount());
    assert("The count of the upper witness was wrong" && cfg->recordCount == upper.getCount());
    assert("The sorting of the witnesses should have been the same" && upper.isSorted == lower.isSorted);
}

void testDropOne() {
    SorterConfig* cfg = new SorterConfig();
    string file = "../ExampleFiles/input_table";
    cfg->recordCount = 20;
    cfg->recordSize = 1024;
    RecordProvider generator(*cfg, file);
    Witness lower(&generator);
    NoopSorter sorter(&lower);
    Witness upper(&sorter);
    Dedooper dooper(&upper);
    Consumer consumer(&dooper);
    consumer.consume();

    assert("The count of the lower witness did not equal the count of the upper but should have" && lower.getCount() == upper.getCount());
    assert("The count of the upper witness was wrong" && cfg->recordCount == upper.getCount());
    assert("The sorting of the witnesses should have been the same" && upper.isSorted == lower.isSorted);
}

void testTreeSorter() {
    SorterConfig* cfg = new SorterConfig();
    string file = "../ExampleFiles/input_table";
    cfg->recordCount = 20;
    cfg->recordSize = 1024;
    RecordProvider generator(*cfg, file);
    Witness lower(&generator);
    TreeSorter sorter(&lower);
    Witness upper(&sorter);
    Dedooper dooper(&upper);
    Consumer consumer(&dooper);
    consumer.consume();
    assert(("The count of the lower witness was wrong" &&  cfg->recordCount == lower.getCount()));
    assert(("The count of the upper witness was wrong" &&  cfg->recordCount == upper.getCount()));
    assert(("The upper witness should have been sorted but was not" && upper.isSorted));
    assert(("The lower witness should not have been sorted but was" && !lower.isSorted));
    assert(("The checksum of the lower witness did not equal the checksum of the upper but should have" && lower.getCrc() == upper.getCrc()));
}

int main(){
    testNext();
    testInputRecord();
    testDropOne();
    testTreeSorter();
}