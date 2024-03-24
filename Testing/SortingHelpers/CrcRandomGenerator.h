#ifndef CS764_SORTER_CRCRANDOMGENERATOR_H
#define CS764_SORTER_CRCRANDOMGENERATOR_H
#include <stdlib.h>
#include "../../Records/Record.h"
#include "../../Providers/Provider.h"


class CrcRandomGenerator: public Provider{
public:
    long count;
    uint64_t size;
    uint32_t keyOffset;
    CrcRandomGenerator(long count, uint64_t size, uint32_t keyOffset);
    Record* next();
    bool verifyCrc(Record* recPtr);
private:
    long generated = 0;
};


#endif //CS764_SORTER_CRCRANDOMGENERATOR_H
