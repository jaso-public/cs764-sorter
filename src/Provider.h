#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "Record.h"

using namespace std;

/**
 * This is the provider class that will generate all the desired records
 * it provides an a virtual method that all other providers implement.
 * You call next to receive the records in some order depending on where
 * the records are coming from, for example if the records are being provided
 * by a file, then the records will arrive in the order they are stored in
 * the file, if the provider is the Sorter, then the records will be provided
 * in sorted order. There are many different providers, the simplest one are
 * defined in the header file.
 */
class Provider {

public:
    /**
     * Generates the next record
     * @returns the a pointer to the next record or a null pointer record if the end of the list been reached
     */
    virtual ~Provider() {}
    virtual shared_ptr<Record> next() = 0;
};

/**
 * A single provider is a simple provider that can be reused.  The reset method
 * provides the provider with a single record that will be returned the next
 * time that the next() method is called.  The record is only returned once, so
 * after returning the reset record, the next() will continue to return nullptr.
 */
class SingleProvider: public Provider {
public:
    SingleProvider(): record(nullptr) {}

    /**
     * Sets the class record's variable to the given record
     * @param r the new record variable of the class
     */
    void reset(shared_ptr<Record> r) {
        record = r;
    }

    // returns the class record's variable and then turns it to null
    shared_ptr<Record> next() override {
        shared_ptr<Record> result = record;
        record = nullptr;
        return result;
    }

private:
    shared_ptr<Record> record; // a pointer to a record or a null pointer if the record does not exist
};

/**
 * The memory provider extracts records from packed buffer of records.
 * The memory buffer requires that records are stored in the buffer one
 * after another and that each record consumes exactly recordSize number
 * of byte.  You must know how many records are stored in the buffer when
 * you use the MemoryProvider (There are no sentinels in the buffers)
 */
class MemoryProvider: public Provider {
public:
    MemoryProvider(uint8_t *_buffer, uint32_t _recordCount): buffer(_buffer), recordCount(_recordCount), generatedRecordCount(0) {}

    shared_ptr<Record> next() override {
        if(generatedRecordCount >= recordCount) return nullptr;

        int recordSize = Record::getRecordSize();

        uint32_t offset = generatedRecordCount * recordSize;

        unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(recordSize);
        memcpy(data.get(), buffer + offset, recordSize);

        generatedRecordCount++;
        return make_shared<Record>(data);
    }

private:
    uint8_t *buffer; // the buffer holding the record data
    uint64_t generatedRecordCount;
    uint64_t recordCount;
};


/**
 * This class is an empty provider that continues to return a nullptr
 * everytime next() is called.  It the provider used by the Sorter when
 * there are no records to be sorted.
 */
class EmptyProvider: public Provider {
public:
    EmptyProvider() {}

    shared_ptr<Record> next() override {
        return nullptr;
    }
};

/**
 * TODO docs
 */
class ArrayProvider: public Provider {

public:
    ArrayProvider(string name, vector <shared_ptr<Record>> _records) : name(name), records(_records), iter(records.begin()) {}

    shared_ptr<Record> next() override {
        if (iter == records.end()) return nullptr;
        shared_ptr<Record> result = *iter;
        iter++;
        return result;
    }

private:
    string name; // name to identify the record array
    vector<shared_ptr<Record>> records; // vector of record pointers that will be used for iteration
    vector<shared_ptr<Record>>::iterator iter; // iterator to return the records
};


/**
 * TODO docs
 */
class InputStreamProvider: public Provider {
public:
    InputStreamProvider(string filePath);
    ~InputStreamProvider();
    shared_ptr<Record> next() override;

private:
    string filePath;
    ifstream* streamPtr;
    bool eofReached;
};

/**
 * TODO docs
 */
class OutputStreamProvider: public Provider {
public:
    OutputStreamProvider(string filePath, shared_ptr<Provider> _source);
    ~OutputStreamProvider();
    shared_ptr<Record> next() override;

private:
    string filePath;
    ifstream* streamPtr;
    bool eofReached;
};


