#ifndef CS764_SORTER_TREESORTER_H
#define CS764_SORTER_TREESORTER_H
#include "../../Providers/Provider.h"
#include "../../Records/Record.h"
#include "Key.h"
#include <vector>
#include "Key.h"
#include <map>
using namespace std;


class TreeSorter: public Provider{
public:
    Record* next() override;
    TreeSorter(Provider source);

private:
    // iterator to return the records
    vector<Record>::iterator iterator;
    vector<Record> records;

};


#endif //CS764_SORTER_TREESORTER_H
