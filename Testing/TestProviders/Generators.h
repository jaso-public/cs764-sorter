#ifndef CS764_SORTER_GENERATORS_H
#define CS764_SORTER_GENERATORS_H

#include <cstdlib>
#include <cstdint>
#include <memory>
#include <random>

#include "./Records/Record.h"

vector<shared_ptr<Record>> generateInOrder(int recordCount);
vector<shared_ptr<Record>> generateRandom(int recordCount);
vector<shared_ptr<Record>> generateDuplicates(int recordCount);

#endif //CS764_SORTER_GENERATORS_H
