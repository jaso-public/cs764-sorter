#include "InOrderGenerator.h"

// class constructor
InOrderGenerator::InOrderGenerator(long count, uint64_t size, uint32_t keyOffset, uint32_t keySize) {
    // sets given variables to class variables
    this->count = count;
    this->size = size;
    this->keyOffset = keyOffset;
    this->generated = 0;
    this->keySize = keySize;
}

/**
    * Continues to generate a new record in memory until records of the desired count have been generated
    * @return a pointer to the next record or a null pointer if count has been reached
    */
shared_ptr<Record> InOrderGenerator::next() {
    // returns a null pointer when no more records are to be generated
    if (generated >= count) return nullptr;
    // returns a newly created record in memory
    Record::staticInitialize(size, keyOffset, keySize);
    generated++;
    shared_ptr<Record> ptr(new Record);
    return ptr;
}
