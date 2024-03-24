#include "CrcRandomGenerator.h"
using namespace std;

CrcRandomGenerator::CrcRandomGenerator(long count, uint64_t size, uint32_t keyOffset) {
    this->count = count;
    this->size = size;
    this->keyOffset = keyOffset;
}

Record* CrcRandomGenerator::next() {
    if(generated >= count) return nullptr;
    Record r(size, keyOffset);
    generated++;
    Record* ptr = &r;
    return ptr;
}

bool CrcRandomGenerator::verifyCrc(Record* recordPtr) {
    if (!recordPtr) return true;
    Record r = *recordPtr;
    return r.completeChecksumCheck();
}