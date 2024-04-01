#include "CrcRandomGenerator.h"


CrcRandomGenerator::CrcRandomGenerator(long count, uint64_t size, uint32_t keyOffset, uint32_t keySize) {
    this->keySize = keySize;
    this->count = count;
    this->size = size;
    this->keyOffset = keyOffset;
    this->generated = 0;
}

shared_ptr<Record> CrcRandomGenerator::next() {
    if(generated >= count) return nullptr;
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
