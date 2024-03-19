#ifndef CS764_SORTER_SORTER_H
#define CS764_SORTER_SORTER_H
#include "Providers/Provider.h"
#include "SorterConfig.h"
#include "Run.h"
#include <vector>

class Sorter: Provider {
private:
    SorterConfig cfg;
    Provider source;
    int recordSize;
    Provider sortedProvider;

     long ssdOffset = 0;
     long ssdRemaining = 0;
     long hddOffset = 0;

     char * buffer;
     int lastMemoryRun;

     Provider startSort();
     void makeFreeSpace();
     void releaseMemory(int numberBuffersToRelease);
     void storeRun(Provider provider, long recordCount);
     long roundUp(long value, long multiple);
public:
    vector<Run> memoryRuns;
    vector<Run> ssdRuns;
    vector<Run> hddRuns;
    Sorter(SorterConfig cfg, Provider source, int recordSize);
    Record* next();
    void printStats();

};


#endif //CS764_SORTER_SORTER_H
