#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(SorterConfig cfg) {
    this->cfg = &cfg;
    this->generated = 0;
}

shared_ptr<Record> RandomGenerator::next() {
    if(generated >= cfg->recordCount) return nullptr;
    generated++;
    shared_ptr<Record> ptr(new Record);
    return ptr;
}
