#ifndef CS764_SORTER_REMOVEDUPLICATES_H
#define CS764_SORTER_REMOVEDUPLICATES_H
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
using namespace std;


class RemoveDuplicates {
public:
    RemoveDuplicates(string inputFile, string outputFile);
    void removeDuplicates();
    string inputFile;
    string outputFile;
};


#endif //CS764_SORTER_REMOVEDUPLICATES_H
