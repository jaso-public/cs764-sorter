#include "Provider.h"

#include "RecordProvider.h"

RecordProvider::RecordProvider(SorterConfig cfg, string filePath) {
    this->cfg = &cfg;
    this->filePath = filePath;
    this->generated = 0;
    // opens for reading
    this->streamPtr = new ifstream (filePath, std::ios::binary);
    if (!streamPtr->is_open()) {
        cerr << "Error opening: " << filePath << "\n";
        delete streamPtr;
        streamPtr = nullptr;
    }
    (*streamPtr).seekg(0, ios::beg);
}

RecordProvider::~RecordProvider() {
    if (streamPtr) {
        streamPtr->close();
        delete streamPtr;
    }
}

shared_ptr<Record> RecordProvider::next() {
    if (!streamPtr) {
        cerr << "File not open for reading\n";
        return nullptr;
    }
    // catches exception if file cannot be read
    (*streamPtr).exceptions ( fstream ::badbit );
    try {
        if (generated >= cfg->recordCount) return nullptr;
        uint8_t* data = new uint8_t[cfg->recordSize];
        Record::staticInitialize(cfg->recordSize, cfg->keyOffset, cfg->keySize);
        (*streamPtr).read(reinterpret_cast<char*>(data), cfg->recordSize);
        shared_ptr<Record> ptr(new Record(data));
        generated++;
        // moves pointer to position of next record
        (*streamPtr).seekg(cfg->recordSize);
        return ptr;
    }
        // catches failure reading file
    catch (ios_base ::failure e) {
        cerr << "Error reading: " << filePath << " to obtain record";
        return nullptr;
    }
}



