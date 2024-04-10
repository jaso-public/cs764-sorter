#include "TreeSorter.h"

bool customCompare(const shared_ptr<Record>& a, const shared_ptr<Record>& b) {
    int cmp = a->compareTo(b);
    return cmp <= 0;
}

TreeSorter::TreeSorter(shared_ptr<Provider> source) {
    // adds all record to TreeMap until count has been reached
    while(true) {
        shared_ptr<Record> recordPtr = source->next();
        if(recordPtr == nullptr) break;
        records.push_back(recordPtr);
    }

    std::sort(records.begin(), records.end(), customCompare);
    iter = records.begin();
}

shared_ptr<Record> TreeSorter::next() {
    // checks that another record exists
    if (iter == records.end()) return nullptr;
    return *iter++;
 }
