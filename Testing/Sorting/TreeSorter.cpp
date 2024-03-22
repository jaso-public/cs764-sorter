#include "TreeSorter.h"

TreeSorter::TreeSorter(Provider source) {
    long index = 0;
    TreeMap<Key,Record> sorted = new TreeMap<>();
    // adds all record to TreeMap until count has been reached
    while(true) {
        Record* recordPtr = source.next();
        if(!recordPtr) break;
        Record record = *recordPtr;
        Key key(record.getRecordKey(), index++)
        sorted.put(key, record);
    }
    records = sorted.values().iterator();
}

Record *TreeSorter::next() {

}