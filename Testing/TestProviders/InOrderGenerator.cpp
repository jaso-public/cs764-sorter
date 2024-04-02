#include "InOrderGenerator.h"

// class constructor
InOrderGenerator::InOrderGenerator(SorterConfig cfg) {
    // sets given variables to class variables
    this->cfg = &cfg;
    this->generated = 0;
}

/**
    * Continues to generate a new record in memory until records of the desired count have been generated
    * @return a pointer to the next record or a null pointer if count has been reached
    */
shared_ptr<Record> InOrderGenerator::next() {
    // returns a null pointer when no more records are to be generated
    if (generated >= cfg->recordCount) return shared_ptr<Record>();
    // returns a newly created record in memory
    Record::staticInitialize(cfg->recordSize, cfg->keyOffset, cfg->keySize);
    generated++;
    shared_ptr<Record> ptr(new Record());
    return ptr;
}
