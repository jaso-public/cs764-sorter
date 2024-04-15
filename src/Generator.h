#ifndef CS764_SORTER_GENERATOR_H
#define CS764_SORTER_GENERATOR_H

#include <cstdlib>
#include <cstdint>
#include <memory>
#include <random>

#include "Record.h"


shared_ptr<Record> makeRandomRecord(std::mt19937 &gen, bool newLine);
shared_ptr<Record> makeIntegerRecord(uint32_t value, bool newLine);

// TODO remove these
vector<shared_ptr<Record>> generateInOrder(int recordCount);
vector<shared_ptr<Record>> generateRandom(int recordCount, bool newLine);
vector<shared_ptr<Record>> generateRandom(int recordCount);

bool isCrcValid(shared_ptr<Record> record);
#endif //CS764_SORTER_GENERATOR_H
