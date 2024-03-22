#include "CrcRandomGenerator.h"
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
using namespace std;

using random_bytes_engine = std::independent_bits_engine<
        std::default_random_engine, CHAR_BIT, unsigned char>;

CrcRandomGenerator::CrcRandomGenerator(long count, int size) {
    this->count = count;
    this->size = size;
}

//TODO: this method is a template method
Record* CrcRandomGenerator::next() {
    if(generated >= count) return nullptr;
    //places the generated random bytes into vector r
    random_bytes_engine rbe;
    vector<unsigned char> r(1000);
    generate(begin(r), end(r), std::ref(rbe));

    Record* ptr = nullptr;
    return nullptr;
}

//TODO: this method is a template method
void CrcRandomGenerator::verifyCrc(Record rec) {

}