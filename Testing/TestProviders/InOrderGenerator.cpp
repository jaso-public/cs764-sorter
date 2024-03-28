#include "InOrderGenerator.h"

// class constructor
InOrderGenerator::InOrderGenerator(long count, uint64_t size, uint32_t keyOffset) {
    // sets given variables to class variables
    this->count = count;
    this->size = size;
    this->keyOffset = keyOffset;
    this->generated = 0;
}

/**
    * Continues to generate a new record in memory until records of the desired count have been generated
    * @return a pointer to the next record or a null pointer if count has been reached
    */
Record* InOrderGenerator::next() {
    // returns a null pointer when no more records are to be generated
    if (generated >= count) return nullptr;
    // returns a newly created record in memory
    Record r;
    r.staticInitialize(c)
    generated++;
    Record* ptr = &r;
    return ptr;
}
