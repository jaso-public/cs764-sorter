#ifndef CS764_SORTER_DEDOOPER_H
#define CS764_SORTER_DEDOOPER_H

#include "Provider.h"
#include <memory>
#include <iostream>
using namespace std;


class Dedooper: public Provider{
public:
    Provider* source;
    Dedooper(Provider* source);
    shared_ptr<Record> next();
private:
    shared_ptr<Record> previousRecord;
};


#endif //CS764_SORTER_DEDOOPER_H