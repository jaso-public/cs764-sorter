#include "Sorter.h"
#include "Providers/SingleProvider.h"
#include "Providers/EmptyProvider.h"
#include "TournamentPQ.h"
#include "./Records/Record.h"
#include "./Records/Record.cpp"

Sorter::Sorter(SorterConfig cfg, Provider source, int recordSize,     uint32_t keyOffset) {
   //TODO: fix this
    this->cfg = cfg;
    this->source = source;
    this->recordSize = recordSize;
    this->keyOffset = keyOffset;
    Record r();
    this->record = r();


    ssdRemaining = cfg.ssdStorageSize;

    this->buffer = new char[cfg.memoryBlockSize * cfg.memoryBlockCount];
    lastMemoryRun = sizeof(buffer);

    this->sortedProvider = startSort();
}

Record* Sorter::next() {
    return sortedProvider.next();
}

Provider Sorter::startSort() {
    Record r();
    r().resetCompareCount();

    int maxRecordsPerRun = cfg.memoryBlockSize / recordSize;

    SingleProvider s();
    vector<SingleProvider> singles();
    //TODO:
   // singles(maxRecordsPerRun,s);

    bool endReached = false;
    while(!endReached) {
        int recordCount = 0;
        while(recordCount < maxRecordsPerRun) {
            Record* recordPtr = source.next();
            if(!recordPtr) {
                endReached = true;
                break;
            }
            //TODO:
            //singles[recordCount++].reset(r);
        }

        if(recordCount > 0) {
            // find the buffer that we are going to fill.
            if(lastMemoryRun == cfg.memoryBlockSize) makeFreeSpace();

            lastMemoryRun -= cfg.memoryBlockSize;

            TournamentPQ pq(singles(), keyOffset, recordCount);
            for(int i=0 ; i<recordCount ; i++) {
                Record* ptr = pq.next();
                Record r = *ptr;
                r.store(buffer, lastMemoryRun + i * recordSize);
            }
            Run run(recordCount, lastMemoryRun);
            memoryRuns.push_back(run);
        }

    }
    // if there was nothing to sort then return an empty provider.
    if(memoryRuns.size() + ssdRuns.size() + hddRuns.size() == 0) {
        EmptyProvider e();
        return reinterpret_cast<Provider &&>(e);
    }

    // see if we can do the final merge with the memory we have.
    // i.e not too many runs and no need to stage hdd runs to ssd
    int memoryRequired = ssdRuns.size() * cfg.ssdReadSize + (hddRuns.size() + 1) * cfg.hddReadSize;
    if(memoryRequired < cfg.memoryBlockCount * cfg.memoryBlockSize) {
        if(memoryRequired > lastMemoryRun) {
            int toRelease = (memoryRequired - lastMemoryRun + cfg.memoryBlockSize - 1) / cfg.memoryBlockSize;
            releaseMemory(toRelease);
        }

        vector<Provider> providers(memoryRuns.size() + ssdRuns.size() + hddRuns.size());
        int index = 0;

        for(Run run : memoryRuns) {
            //TODO: here
         //   providers[index++] = MemoryProvider m(buffer, run.offset, run.numRecords, recordSize);
        }
    }


}