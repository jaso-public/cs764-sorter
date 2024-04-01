#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(long count, uint64_t size, uint32_t keyOffset) {
    this->count = count;
    this->size = size;
    this->keyOffset = keyOffset;
    this->generated = 0;
}

shared_ptr<Record> RandomGenerator::next() {
    if(generated >= count) return nullptr;
    generated++;
    shared_ptr<Record> ptr(new Record);
    return ptr;
}
