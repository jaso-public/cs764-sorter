#ifndef CS764_SORTER_SORTER_H
#define CS764_SORTER_SORTER_H
#include "../Providers/Provider.h"
#include "../Config/SorterConfig.h"
#include "../Run.h"
#include "../Records/Record.h"
#include "Providers/SingleProvider.h"
#include "Providers/EmptyProvider.h"
#include "Providers/MemoryProvider.h"
#include "Providers/StorageProvider.h"
#include "Providers/StagedProvider.h"
#include "TournamentPQ.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Sorter: public Provider, public Record{
private:
    SorterConfig cfg;
    Provider* source;
    int recordSize;

    Provider* sortedProvider;
    Record record;


     long ssdOffset;
     long ssdRemaining;
     long hddOffset;

     uint8_t *buffer;
     int lastMemoryRun;

     Provider* startSort();

     void makeFreeSpace();
     void releaseMemory(int numberBuffersToRelease);
     void storeRun(Provider* provider, long recordCount);
     long roundUp(long value, long multiple);

public:
    vector<Run> memoryRuns;
    vector<Run> ssdRuns;
    vector<Run> hddRuns;
    Sorter(SorterConfig cfg, Provider* source, int recordSize, uint32_t keyOffset);
    Record* next() override;
    void printStats();

};


#endif //CS764_SORTER_SORTER_H
