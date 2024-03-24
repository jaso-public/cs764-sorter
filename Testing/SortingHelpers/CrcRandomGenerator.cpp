#include "CrcRandomGenerator.h"
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
using namespace std;

using random_bytes_engine = std::independent_bits_engine<
        std::default_random_engine, CHAR_BIT, unsigned char>;

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
    if (!recordPtr) return;
    Record r = *recordPtr;
    return r.completeChecksumCheck();
}