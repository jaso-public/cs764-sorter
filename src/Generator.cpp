#include "Generator.h"


shared_ptr<Record> makeRandomRecord(std::mt19937 &gen, bool newLine) {
    int recordSize = Record::getRecordSize();
    std::uniform_int_distribution<> distrib(0, 61);
    auto buffer = std::make_unique<uint8_t[]>(recordSize);

    for (int i = 0; i < recordSize; i++) {
        uint8_t value = distrib(gen);
        if (value < 26) {
            buffer[i] = value + 'A';
        } else if (value < 52) {
            buffer[i] = value - 26 + 'a';
        } else {
            buffer[i] = value - 52 + '0';
        }
    }

    if(newLine) buffer[recordSize-1] = '\n';
    return make_shared<Record>(buffer);
}


shared_ptr<Record> makeIntegerRecord(uint32_t value, bool newLine) {
    int recordSize = Record::getRecordSize();
    auto buffer = std::make_unique<uint8_t[]>(recordSize);

    // fill the buffer with '0's
    memset(buffer.get(), '0', recordSize);

    // write the value to a temporary buffer
    int size = 12;
    char intStr[size];
    snprintf(intStr, size, "%010u", value);

    // copy the buffer into the record
    int sizeToCopy = strlen(intStr);
    if(sizeToCopy > recordSize) sizeToCopy = recordSize;
    memcpy(buffer.get(), intStr, sizeToCopy);

    if(newLine) buffer[recordSize-1] = '\n';
    return make_shared<Record>(buffer);
}

vector<shared_ptr<Record>> generateInOrder(int recordCount) {
    vector<shared_ptr<Record>> result;
    for(int i=0 ; i<recordCount ; i++) {
        result.push_back(makeIntegerRecord(i, true));
    }
    return result;
}

vector<shared_ptr<Record>> generateRandom(int recordCount, bool newLine) {
    vector<shared_ptr<Record>> result;
    std::random_device rd; // Obtain a seed from the system entropy device, or use a fixed seed for reproducible results
    std::mt19937 gen(rd()); // Seed the generator

    for(int i=0 ; i<recordCount ; i++) {
        result.push_back(makeRandomRecord(gen, newLine));
    }
    return result;
}

vector<shared_ptr<Record>> generateRandom(int recordCount) {
    return generateRandom(recordCount, false);
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

