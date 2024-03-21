#ifndef CS764_SORTER_CRCRANDOMGENERATOR_H
#define CS764_SORTER_CRCRANDOMGENERATOR_H
#include <stdlib.h>
#include "../Records/Record.h"


class CrcRandomGenerator {
public:
    long count;
    int size;
    CrcRandomGenerator(long count, int size);
    Record* next();
    void verifyCrc(Record rec);
private:
    long generated = 0;
    int rng = rand();
};


#endif //CS764_SORTER_CRCRANDOMGENERATOR_H
