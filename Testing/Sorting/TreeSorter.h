#ifndef CS764_SORTER_TREESORTER_H
#define CS764_SORTER_TREESORTER_H
#include "../../Providers/Provider.h"
#include "../../Records/Record.h"


class TreeSorter: public Provider{
public:
    Record* next();
    TreeSorter(Provider source);

};


#endif //CS764_SORTER_TREESORTER_H
