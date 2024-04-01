#include "TreeSorter.h"

TreeSorter::TreeSorter(Provider* source) {
    this->source = source;
    map<Record,Record> sorted;
    // adds all record to TreeMap until count has been reached
    while(true) {
        shared_ptr<Record> recordPtr = source->next();
        if(!recordPtr) break;
        Record record = *recordPtr;
        sorted[record] = record;
    }

    map<Record, Record>::iterator it = sorted.begin();
    vector<Record> currentRecords;
    // getting all records from sorted list
    while (it != sorted.end()) {
        Record r = it->second;
        currentRecords.push_back(r);
        it++;
    }
    this->records = currentRecords;
    this->iterator = records.begin();
}

shared_ptr<Record> TreeSorter::next() {
    // checks that another record exists
    if (iterator < records.end()){
        // create a pointer to the returned record
        Record result = *iterator;
        shared_ptr<Record> recordPtr =  &result;
        iterator++;
        return recordPtr;
    }
    return nullptr;
}
