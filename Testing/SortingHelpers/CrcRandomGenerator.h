#ifndef CS764_SORTER_CRCRANDOMGENERATOR_H
#define CS764_SORTER_CRCRANDOMGENERATOR_H
#include <stdlib.h>
#include "../../Records/Record.h"
#include "../../Providers/Provider.h"
#include "Config/SorterConfig.h"
using namespace std;

class CrcRandomGenerator: public Provider{
public:
    CrcRandomGenerator(SorterConfig cfg);
    shared_ptr<Record> next() override;
    bool verifyCrc(shared_ptr<Record> recordPtr);
private:
    SorterConfig cfg;
    long generated;
};


#endif //CS764_SORTER_CRCRANDOMGENERATOR_H
