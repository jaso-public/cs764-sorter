#include "Sorter.h"
#include "Providers/SingleProvider.h"
#include "Providers/EmptyProvider.h"
#include "TournamentPQ.h"
#include "./Records/Record.h"
#include "./Records/Record.cpp"
#include "stdint.h"
#include <iostream>
using namespace std;

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

//TODO: finish start sort
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

void Sorter::makeFreeSpace() {
    long sorted = ssdOffset + hddOffset;
    sorted /= cfg.memoryBlockSize;
    sorted += memoryRuns.size();
    // at this point sorted contains the number of 1MB blocks we have.

    int numToMove = (int)(sorted * cfg.fraction);
    if(numToMove < 1) numToMove = 1;

    releaseMemory(numToMove);
}



//TODO: this method
void Sorter::storeRun(Provider provider, long recordCount) {
    long spaceRequired = recordCount * recordSize;

    IODevice device();
    long deviceOffset = 0;

    long ssdRequired = roundUp(spaceRequired, cfg.ssdReadSize);
    if(ssdRequired <= ssdRemaining) {
        device = cfg.ssdDevice;
        deviceOffset = ssdOffset;
        ssdRuns.add(new Run(recordCount, ssdOffset));
        ssdOffset += ssdRequired;
        ssdRemaining -= ssdRequired;
    } else {
        long hddRequired = roundUp(spaceRequired, cfg.hddReadSize);
        device = cfg.hddDevice;
        deviceOffset = hddOffset;
        hddRuns.add(new Run(recordCount, hddOffset));
        hddOffset += hddRequired;
    }

}

long Sorter::roundUp(long value, long multiple) {
    long quotient = value / multiple;
    if(quotient * multiple == value) return value;
    return (quotient + 1) * multiple;
}

void Sorter::printStats(){
    cout << "SSD usage:" << cfg.ssdDevice.stats() << "/";
    cout << "HDD usage:" << cfg.hddDevice.stats() << "/";
    cout << "total number of record comparisons: " <<  record.getCompareCount() << "/";
}