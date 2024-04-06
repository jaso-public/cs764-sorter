#ifndef CS764_SORTER_ARRAYPROVIDER_H
#define CS764_SORTER_ARRAYPROVIDER_H

#include <string>
#include <iostream>
#include <iterator>
#include <vector>

#include "Record.h"
#include "Provider.h"

using namespace std;


/**
 * This class will create an iterator of records to continously reutrn until no records are left
 */
class ArrayProvider: public Provider {

public:
    ArrayProvider(string name, vector <shared_ptr<Record>> _records) : name(name), records(_records), iter(records.begin()) {}

    shared_ptr<Record> next() override {
        cout << "in next\n";
        if (iter == records.end()) return nullptr;
        shared_ptr<Record> result = *iter;
        iter++;
        return result;
    }

private:
    string name; // name to identify the record array
    vector <shared_ptr<Record>> records; // vector of record pointers that will be used for iteration
    vector<shared_ptr<Record>>::iterator iter; // iterator to return the records
};
#endif //CS764_SORTER_ARRAYPROVIDER_H
