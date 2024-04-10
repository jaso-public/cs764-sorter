#include "Generator.h"


void fill_buffer(unique_ptr<uint8_t[]> &buffer, std::mt19937 &gen) {
    std::uniform_int_distribution<> distrib(0, 61);
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
}

vector<shared_ptr<Record>> generateInOrder(int recordCount) {

    vector<shared_ptr<Record>> result;

    std::random_device rd; // Obtain a seed from the system entropy device, or use a fixed seed for reproducible results
    std::mt19937 gen(rd()); // Seed the generator

    int recordSize = Record::getRecordSize();

    int keySize = 10;
    if(keySize+1>=recordSize) keySize = recordSize - 1;

    char *temp = new char[keySize + 1];

    for (uint64_t n = 0; n < recordCount; n++) {
        auto buffer = std::make_unique<uint8_t[]>(recordSize);

        fill_buffer(buffer, gen);

        snprintf(temp, keySize + 1, "%0*llu", keySize, n);
        memcpy(buffer.get(), temp, keySize);
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

    for (uint64_t n = 0; n < recordCount; n++) {
        auto buffer = std::make_unique<uint8_t[]>(recordSize);
        fill_buffer(buffer, gen);
        result.push_back(std::make_shared<Record>(buffer));
    }

    return result;
}

vector<shared_ptr<Record>> generateDuplicate(int recordCount) {
    return generateRandom(recordCount);
}

vector<shared_ptr<Record>> generateRandomWithCrc(int recordCount) {
    vector<shared_ptr<Record>> results = generateRandom(recordCount);

    //TODO actually add the crc

    return results;
}

bool isCrcValid(shared_ptr<Record> record) {
    // TODO actually check the embedded crc value in the record.
    return true;
}

