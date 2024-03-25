#include "RandomGenerator.h"
//TODO: needs to sum class Provider class
RandomGenerator::RandomGenerator(long count, int size) {
    this->count = count;
    this->size = size;
    this->generated = 0;
}

Record* RandomGenerator::next() {
    if(generated >= count) return nullptr;
    generated++;
    Record r(10,8);
    Record* ptr = &r;
    return ptr;
}

int main(){};