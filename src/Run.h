#ifndef CS764_SORTER_RUN_H
#define CS764_SORTER_RUN_H

// TODO move this into the Sorter.h file
class Run {
public:
    Run(long numRecords, long offset): numRecords(numRecords), offset(offset);
    long numRecords;
    long offset;
};

#endif //CS764_SORTER_RUN_H
