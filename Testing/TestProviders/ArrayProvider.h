#include <string>
#include <iostream>
#include<iterator>
#include<vector>
#include "./Records/Record.h"
#include "./Providers/Provider.h"
#include <string>
#include<iterator>
#include<vector>
using namespace std;
#ifndef CS764_SORTER_ARRAYPROVIDER_H
#define CS764_SORTER_ARRAYPROVIDER_H



/**
 * This class will create an iterator of records to continously reutrn until no records are left
 */
class ArrayProvider: public Provider{
private:
    // name to identify the record array
    string name;
    // vector of record pointers that will be used for iteration
    vector<Record> records;
    // iterator to return the records
    vector<Record>::iterator ptr;
public:
    // class constructor
    ArrayProvider(string givenName,  vector<Record> givenRecords);
    // returns a record pointer to the next record or a null pointer if no more records exist
    Record* next() override;
};


#endif //CS764_SORTER_ARRAYPROVIDER_H
