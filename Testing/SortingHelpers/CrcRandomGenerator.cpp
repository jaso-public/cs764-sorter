#include "CrcRandomGenerator.h"


CrcRandomGenerator::CrcRandomGenerator(SorterConfig cfg) {
    this->cfg = &cfg;
    this->generated = 0;
}

shared_ptr<Record> CrcRandomGenerator::next() {
    if(generated >= cfg.recordCount) return nullptr;
    Record::staticInitialize(cfg.recordSize, cfg.keyOffset, cfg.keySize);
    uint8_t* data = new uint8_t[cfg.recordSize];
    fill(cfg.recordSize, data);
    generated++;
    shared_ptr<Record> ptr(new Record(data));
    return ptr;
}

bool CrcRandomGenerator::verifyCrc(shared_ptr<Record> recordPtr) {
    if (!recordPtr) return false;
    Record r = *recordPtr;
    r.data[0] = 5;
    uint64_t checksum = r.checksum();
    r.data[0] = 3;
    uint64_t checksum1 = r.checksum();
    r.data[0] = 5;
    return checksum != checksum1 && checksum == r.checksum();
}
