#include "CrcRandomGenerator.h"


CrcRandomGenerator::CrcRandomGenerator(SorterConfig cfg) {
    this->cfg = cfg;
    this->generated = 0;
}

shared_ptr<Record> CrcRandomGenerator::next() {
    if(generated >= cfg.recordCount) return nullptr;
    uint8_t* data = new uint8_t[cfg.recordSize];
    fill(cfg.recordSize, data);
    generated++;
    shared_ptr<Record> ptr(new Record);
    return ptr;
}

bool CrcRandomGenerator::verifyCrc(shared_ptr<Record> recordPtr) {
    if (!recordPtr) return false;
    Record r = *recordPtr;
    r.data[0] = 5;
    uint64_t checksum = r.checksum();
    r.data[0] = 3;
    uint64_t checksum1 = r.checksum();
    return checksum != checksum1;
}
