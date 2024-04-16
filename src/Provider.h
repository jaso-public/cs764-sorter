#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <random>

#include "Record.h"
#include "IODevice.h"


using namespace std;

/**
 * This is the provider class that will generate all the desired records
 * it provides an a virtual method that all other providers implement.
 * You call next to receive the records in some order depending on where
 * the records are coming from, for example if the records are being provided
 * by a file, then the records will arrive in the order they are stored in
 * the file, if the provider is the Sorter, then the records will be provided
 * in sorted order. There are many different providers, the simplest ones are
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
    SingleProvider();

    /**
     * Sets the class record's variable to the given record
     * @param r the new record variable of the class
     */
    void reset(shared_ptr<Record> r);

    // returns the class record's variable and then turns it to null
    shared_ptr<Record> next() override;

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
    MemoryProvider(uint8_t *_buffer, uint32_t _recordCount);
    shared_ptr<Record> next() override;

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


class RandomProvider: public Provider {
public:
    RandomProvider(int _recordCount);
    RandomProvider(int _recordCount, bool _newLine);
    RandomProvider(int _recordCount, double _duplicateProbability, int _duplicateRange, bool _newLine);
    shared_ptr<Record> next() override; // implementation of the Provider interface

private:
    random_device rd;  // Device to seed the random generators
    mt19937 gen;
    mt19937 duplicateGen;
    std::uniform_real_distribution<> randomProbability; // Probability distribution
    std::uniform_int_distribution<> randomRange;        // Range distribution

    uint64_t recordCount;
    double duplicateProbability;
    bool newLine;
    uint64_t generated;
};


/**
 * DeviceProvider is a provider that read records from a device (file) and
 * providers them to other via the Provider::next method.  This provider
 * will eventually read the entire contents of the file.  If the final
 * read is not a complete records, then provider will write an error
 * message to cerr and will return null instead of a record.
 */
class DeviceProvider: public Provider {
public:
    DeviceProvider(shared_ptr<IODevice> _device, int _bufferSize);
    shared_ptr<Record> next() override;

private:
    shared_ptr<IODevice> device;               // the input device where the records will be read from
    uint64_t deviceOffset;                     // the location where the next buffer should be read
    int bufferSize;                            // the size of the buffer
    int bufferOffset;                          // the offset into the buffer which has already been read
    int bufferRemaining;                       // the number of usable bytes remaining in the buffer
    unique_ptr<uint8_t[]> buffer;              // a smallish buffer to stage data so we don,t make so many os calls
    bool eofReached;                           // true if we have read all the data from the device
};


/**
 * This provider will drop the first record returned by the
 * the source Provider. See the Provider class for how providers
 * are used.
 *
 * THIS CLASS IS ONLY USED FOR TESTING.
 */
class DropFirst: public Provider {
public:
    DropFirst(shared_ptr<Provider> _source);
    shared_ptr<Record> next() override; // see Provider

private:
    shared_ptr<Provider> source; // the source used to get the records
};

