#include "TreeSorter.h"


TreeSorter::TreeSorter(Provider source) {
    int index = 0;
    map<Key*,Record*> sorted;
    map<Key*, Record*>::iterator it = sorted.begin();
    // adds all record to TreeMap until count has been reached
    while(true) {
        Record* recordPtr = source.next();
        if(!recordPtr) break;
        Record record = *recordPtr;
        Key key(record.getRecordKey(), index++);
        Key* keyPtr = &key;
        sorted[keyPtr]= recordPtr;
    }
    vector<Record> currentRecords;
    // getting all records from sorted list
    while (it != sorted.end()) {
        Record* ptr = it->second;
        Record r = *ptr;
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

int main(){};