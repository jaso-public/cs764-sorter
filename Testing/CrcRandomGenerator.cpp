#include "CrcRandomGenerator.h"
CrcRandomGenerator::CrcRandomGenerator(long count, int size) {
    this->count = count;
    this->size = size;
}

Record* CrcRandomGenerator::next() {
    if(generated >= count) return nullptr;
    char * record = new char[size];


}