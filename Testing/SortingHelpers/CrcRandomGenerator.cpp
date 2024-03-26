#include "CrcRandomGenerator.h"


CrcRandomGenerator::CrcRandomGenerator(long count, uint64_t size, uint32_t keyOffset) {
    this->count = count;
    this->size = size;
    this->keyOffset = keyOffset;
    this->generated = 0;
}

Record* CrcRandomGenerator::next() {
    if(generated >= count) return nullptr;
    Record r(size, keyOffset);
    generated++;
    Record* ptr = &r;
    return ptr;
}

//TODO: this may be wrong
bool CrcRandomGenerator::verifyCrc(Record* recordPtr) {
    if (!recordPtr) return true;
    Record r = *recordPtr;
    return r.completeChecksumCheck();
}
