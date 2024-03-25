#ifndef CS764_SORTER_CREATERECORDS_H
#define CS764_SORTER_CREATERECORDS_H
#include <iostream>
#include <fstream>
#include "Record.h"
using namespace std;

/**
 * This is the provider class that will generate all the desired records
 */
class CreateRecords {

public:
    int recordSize;
    int numberOfRecords;
    int generated;
    int data;

    CreateRecords(int recordSize, int numberOfRecords);

    void write();

    void read();
};


#endif //CS764_SORTER_CREATERECORDS_H
