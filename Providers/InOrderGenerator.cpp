#include "InOrderGenerator.h"

// class constructor
InOrderGenerator::InOrderGenerator(long givenCount, int givenSize) {
    // sets given variables to class variables
    this->count = givenCount;
    this->size = givenSize;
}

/**
    * Continues to generate a new record in memory until records of the desired count have been generated
    * @return a pointer to the next record or a null pointer if count has been reached
    */
Record* InOrderGenerator::next() {
    // returns a null pointer when no more records are to be generated
    if (generated >= count) return nullptr;
    // returns a newly created record in memory
    Record r(size, 8);
    generated++;
    Record* ptr = &r;
    return ptr;
}

