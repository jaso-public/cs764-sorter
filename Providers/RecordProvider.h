#ifndef CS764_SORTER_RECORDPROVIDER_H
#define CS764_SORTER_RECORDPROVIDER_H
#include "Provider.h"
#include <stdlib.h>
#include "Config/SorterConfig.h"
#include <memory>
using namespace std;



class RecordProvider: public Provider{
public:
    RecordProvider(SorterConfig cfg, string filePath);
    ~RecordProvider();
    shared_ptr<Record> next() override;
private:
    SorterConfig* cfg;
    string filePath;
    ifstream* streamPtr;
    long generated;
};


#endif //CS764_SORTER_RECORDPROVIDER_H
