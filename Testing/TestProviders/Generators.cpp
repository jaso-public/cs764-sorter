#include "Generators.h"


vector<shared_ptr<Record>> generateInOrder(int recordCount) {

    vector<shared_ptr<Record>> result;

    std::random_device rd; // Obtain a seed from the system entropy device, or use a fixed seed for reproducible results
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distrib(0, 61); // used to get the random characters

    int recordSize = Record::getRecordSize();
    int keySize = Record::getKeySize();
    int keyOffset = Record::getKeyOffset();

    uint8_t *buffer = new uint8_t[recordSize];
    char *temp = new char[keySize + 1];

    for (uint64_t n = 0; n < recordCount; n++) {
        for (int i = 0; i < Record::getRecordSize(); i++) {
            uint8_t value = distrib(gen);
            if (value < 26) {
                buffer[i] = value + 'A';
            } else if (value < 52) {
                buffer[i] = value - 26 + 'a';
            } else {
                buffer[i] = value - 52 + '0';
            }
        }

        snprintf(temp, keySize + 1, "%0*llu", keySize, n);
        memcpy(buffer + keyOffset, temp, keySize);
        buffer[recordSize - 1] = '\n';

        result.push_back(std::make_shared<Record>(buffer));
    }

    return result;
}


vector<shared_ptr<Record>> generateRandom(int recordCount) {

    vector<shared_ptr<Record>> result;

    std::random_device rd; // Obtain a seed from the system entropy device, or use a fixed seed for reproducible results
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distrib(0, 61); // used to get the random characters

    int recordSize = Record::getRecordSize();
    int keySize = Record::getKeySize();
    int keyOffset = Record::getKeyOffset();

    uint8_t *buffer = new uint8_t[recordSize];
    char *temp = new char[keySize + 1];

    for (uint64_t n = 0; n < recordCount; n++) {
        for (int i = 0; i < Record::getRecordSize(); i++) {
            uint8_t value = distrib(gen);
            if (value < 26) {
                buffer[i] = value + 'A';
            } else if (value < 52) {
                buffer[i] = value - 26 + 'a';
            } else {
                buffer[i] = value - 52 + '0';
            }
        }
        result.push_back(std::make_shared<Record>(buffer));
    }

    return result;
}

vector<shared_ptr<Record>> generateDuplicate(int recordCount) {
    return generateRandom(recordCount);
}

