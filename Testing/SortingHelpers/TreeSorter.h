#ifndef CS764_SORTER_TREESORTER_H
#define CS764_SORTER_TREESORTER_H
#include "../../src/Provider.h"
#include "../../src/Record.h"
#include "Key.h"
#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include <string>
using namespace std;


class TreeSorter: public Provider{
public:
    Provider* source;
    shared_ptr<Record> next() override;
    TreeSorter(Provider* source);

private:
    // iterator to return the records
    vector<Record>::iterator iterator;
    vector<Record> records;
};


#endif //CS764_SORTER_TREESORTER_H
