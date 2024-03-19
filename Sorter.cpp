#include "Sorter.h"
#include "Providers/SingleProvider.h"

Sorter::Sorter(SorterConfig cfg, Provider source, int recordSize) {
    this->cfg = cfg;
    this->source = source;
    this->recordSize = recordSize;


    ssdRemaining = cfg.ssdStorageSize;

    this->buffer = new char[cfg.memoryBlockSize * cfg.memoryBlockCount];
    lastMemoryRun = sizeof(buffer);

    this->sortedProvider = startSort();
}

Record* Sorter::next() {
    return sortedProvider.next();
}

//TODO: here
Provider Sorter::startSort() {
    Record.resetCompareCount();

    int maxRecordsPerRun = cfg.memoryBlockSize / recordSize;

    SingleProvider s();
    vector<SingleProvider> singles();


}