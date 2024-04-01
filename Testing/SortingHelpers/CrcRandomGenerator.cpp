#include "CrcRandomGenerator.h"


CrcRandomGenerator::CrcRandomGenerator(SorterConfig cfg) {
    this->cfg = cfg;
    this->generated = 0;
}

shared_ptr<Record> CrcRandomGenerator::next() {
    if(generated >= cfg.recordCount) return nullptr;
    generated++;
    shared_ptr<Record> ptr(new Record);
    return ptr;
}

//TODO: this may be wrong
bool CrcRandomGenerator::verifyCrc(shared_ptr<Record> recordPtr) {
    if (!recordPtr) return true;
    Record r = *recordPtr;
    return r.checksum();
}
