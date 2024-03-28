#ifndef CS764_SORTER_DEDOOPER_H
#define CS764_SORTER_DEDOOPER_H

#include "Provider.h"


class Dedooper: public Provider{
public:
    Provider* source;
    Dedooper(Provider* source);
    Record* next();
};


#endif //CS764_SORTER_DEDOOPER_H