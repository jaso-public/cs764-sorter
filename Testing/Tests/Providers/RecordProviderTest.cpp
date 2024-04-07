#include <cassert>
#include <string>


void testNext() {
    SorterConfig* cfg = new SorterConfig();
    cfg->recordCount = 20;
    cfg->recordSize = 1024;
    string file = "../ExampleFiles/input_table";
    RecordProvider recordProvider(*cfg, file);
    recordProvider.next();
}

void testInputRecord() {
    SorterConfig* cfg = new SorterConfig();
    string file = "../ExampleFiles/input_table";
    cfg->recordCount = 20;
    cfg->recordSize = 1024;
    RecordProvider generator(*cfg, file);
    for (int i = 0; i <     cfg->recordCount; i++){
        shared_ptr<Record> ptr = generator.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = generator.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testTenInOrder() {
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