#ifndef CS764_SORTER_GENERATOR_H
#define CS764_SORTER_GENERATOR_H

#include <cstdlib>
#include <cstdint>
#include <memory>
#include <random>

#include "Record.h"

/**
 * This method will create a randomized record with alphanumerical values
 * @param gen a random number generated
 * @param newLine a true or false value indicating whether or not to include a new line character at the end of the record
 * @return a pointer to a record
 */
shared_ptr<Record> makeRandomRecord(std::mt19937 &gen, bool newLine);
/**
 * This method creates a record filled with the given integer value
 * @param value the integer value to fill the record with
 * @param newLine a true or false value indicating whether or not to include a new line character at the end of the record
 * @return a ponter to a record
 */
shared_ptr<Record> makeIntegerRecord(uint32_t value, bool newLine);

// TODO remove these
vector<shared_ptr<Record>> generateInOrder(int recordCount);
vector<shared_ptr<Record>> generateRandom(int recordCount, bool newLine);
vector<shared_ptr<Record>> generateRandom(int recordCount);

/**
 * This method checks if the CRC value of a record is correct
 * @param record the record to check the CRC value of
 * @return a true or false value indicating if the CRC was valid or not
 */
bool isCrcValid(shared_ptr<Record> record);
#endif //CS764_SORTER_GENERATOR_H
