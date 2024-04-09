#include "TreeSorter.h"

//
//bool operator<(const shared_ptr <Record> &lhs, const shared_ptr <Record> &rhs) {
//    // Assuming records have the same size and key offset
//    return memcmp(lhs.get(), rhs.get(), Record::getKeySize()) < 0;
//}

TreeSorter::TreeSorter(shared_ptr<Provider> source) {
    // adds all record to TreeMap until count has been reached
    while(true) {
        shared_ptr<Record> recordPtr = source->next();
        if(recordPtr == nullptr) break;
        records.push_back(recordPtr);
    }

    std::sort(records.begin(), records.end());
    iter = records.begin();
}

shared_ptr<Record> TreeSorter::next() {
    // checks that another record exists
    if (iter == records.end()) return nullptr;
    return *iter++;
 }
