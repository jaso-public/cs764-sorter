#include "TreeSorter.h"

//TODO: data: data
TreeSorter::TreeSorter(Provider* source) {
    this->source = source;
    int index = 0;
    map<Record,Record> sorted;
    // adds all record to TreeMap until count has been reached
    while(true) {
        Record* recordPtr = source->next();
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

Record* TreeSorter::next() {
    // checks that another record exists
    if (iterator < records.end()){
        // create a pointer to the returned record
        Record result = *iterator;
        Record* recordPtr =  &result;
        iterator++;
        return recordPtr;
    }
    return nullptr;
}
