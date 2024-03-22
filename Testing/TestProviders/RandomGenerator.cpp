#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(long count, int size) {
    this->count = count;
    this->size = size;
}

Record* RandomGenerator::next() {
    if(generated >= count) return nullptr;
    generated++;
    Record r(10,8);
    Record* ptr = &r;
    return ptr;
}
