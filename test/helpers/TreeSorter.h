#ifndef CS764_SORTER_TREESORTER_H
#define CS764_SORTER_TREESORTER_H
#include "src/Provider.h"
#include "src/Record.h"


#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;


class TreeSorter: public Provider{
public:
    TreeSorter(shared_ptr<Provider> source);
    shared_ptr<Record> next() override;

private:
    // iterator to return the records
    vector<shared_ptr<Record>>::iterator iter;
    vector<shared_ptr<Record>> records;
};


#endif //CS764_SORTER_TREESORTER_H
