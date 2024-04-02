#ifndef CS764_SORTER_INORDERGENERATOR_H
#define CS764_SORTER_INORDERGENERATOR_H
#include "./Providers/Provider.h"
#include "Config/SorterConfig.h"
#include <stdlib.h>
#include <memory>
using namespace std;

/**
 * This class can be used to generate records of a certain size and amount
 */
class InOrderGenerator:public Provider {
public:
    // class constructor
    InOrderGenerator(SorterConfig cfg);
    // returns a pointer to the next record or a null pointer if a next record does not exist
    shared_ptr<Record> next() override;
private:
    // stores actual number of records currently generated
    long generated;
    SorterConfig* cfg;
};


#endif //CS764_SORTER_INORDERGENERATOR_H
