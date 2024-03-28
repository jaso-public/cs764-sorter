#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(long count, uint64_t size, uint32_t keyOffset) {
    this->count = count;
    this->size = size;
    this->keyOffset = keyOffset;
    this->generated = 0;
}

Record* RandomGenerator::next() {
    if(generated >= count) return nullptr;
    generated++;
    Record r(size,keyOffset);
    Record* ptr = &r;
    return ptr;
}
