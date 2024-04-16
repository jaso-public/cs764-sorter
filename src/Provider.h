#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <random>

#include "Record.h"
#include "IODevice.h"


using namespace std;

/**
 * This is the provider class that will generate all the desired records.
 * It contains a next() virtual method that all other Providers implement.
 */
class Provider {

public:
    virtual ~Provider() {}
    /**
     * Obtains the next record from the Provider
     * @returns a pointer to the next record or a null pointer if there are no more records left to return
     */
    virtual shared_ptr<Record> next() = 0;
};

/**
 * This is a Provider that only returns a single record that is established by reset().
 */
class SingleProvider: public Provider {
public:
    /**
     * Initializes the class' record variable to null as it needs to be set by reset() first
     */
    SingleProvider();

    /**
     * Sets the class' record variable to the given record
     * @param r the new record of the class to be returned in the next call to next()
     */
    void reset(shared_ptr<Record> r);

    /**
     * Returns the class' record
     * @return the class' record set by reset() or a null pointer if the record has already been returned
     */
    shared_ptr<Record> next() override;

private:
    shared_ptr<Record> record; // a pointer to a record or a null pointer if the record does not exist/already has been returned
};

/**
 * This class extracts records from a packed buffer of records.
 * It requires that records are stored in the buffer one
 * after another and that each record consumes exactly recordSize number
 * of byte.  You must know how many records are stored in the buffer when
 * you use the MemoryProvider (There are no sentinels in the buffers)
 */
class MemoryProvider: public Provider {
public:
    /**
     * Class constructor that initializes class' variables
     * @param _buffer buffer to extract records from
     * @param _recordCount total number of records to extract
     */
    MemoryProvider(uint8_t *_buffer, uint32_t _recordCount);
    /**
     * Gets and returns the next record out of the buffer
     * @return a record or a null pointer if all records have been returned
     */
    shared_ptr<Record> next() override;

private:
    uint8_t *buffer;                  // the buffer holding the record data
    uint64_t generatedRecordCount;    // the total number of records currently returned by the class
    uint64_t recordCount;             // the total number of records to be returned
};


/**
 * This class is an empty provider that continues to return a nullptr
 * everytime next() is called. It is used by the Sorter when
 * there are no records to be sorted.
 */
class EmptyProvider: public Provider {
public:
    EmptyProvider() {}

    /**
     * This method only returns null pointers, indicating that no records are to be returned
     * @return a null pointer
     */
    shared_ptr<Record> next() override {
        return nullptr;
    }
};

/**
 * This class will generate random records. It is utilized for testing purposes.
 */
class RandomProvider: public Provider {
public:
    /**
     * Class constructor that accepts a given record count specification
     * @param _recordCount total number of records to return by next()
     */
    RandomProvider(int _recordCount);
    /**
    * Class constructor that accepts a given record count and can add a new line character to the end of each record
    * @param _recordCount total number of records to return by next()
     *@param _newLine boolean value indicating whether or not to include a new line character to the end of the record
    */
    RandomProvider(int _recordCount, bool _newLine);
    /**
     * Class constructor that accepts a user's input for all values involved in generating records
     * @param _recordCount total number of records to return by next()
     * @param _duplicateProbability the percentage of records to generate records within the specified range
     * @param _duplicateRange the upper bound of the range to generate records within the probability percentage between
     * @param _newLine boolean value indicating whether or not to include a new line character to the end of the record
     */
    RandomProvider(int _recordCount, double _duplicateProbability, int _duplicateRange, bool _newLine);
    /**
     * Generates a record with the defined characteristics from the constructor
     * @return the generated record or a null pointer if all records have been generated
     */
    shared_ptr<Record> next() override;

private:
    random_device rd;                                   // device to seed the random generators
    mt19937 gen;                                        // seed the main generator
    mt19937 duplicateGen;                               // seed the duplicate generator
    std::uniform_real_distribution<> randomProbability; // probability distribution
    std::uniform_int_distribution<> randomRange;        // range distribution

    uint64_t recordCount;                               // total number of records to generate
    double duplicateProbability;                        // percentage of records to generate within the specified range
    bool newLine;                                       // indicating if a new line character should be added at the end of a record
    uint64_t generated;                                 // total number of record already generated
};


/**
 * DeviceProvider is a provider that read records from a device (file)
 * until the next() method has returned all records or encountered an error
 */
class DeviceProvider: public Provider {
public:
    /**
     * Class constructor that initializes class' values
     * @param _device the device that will read the records from the file
     * @param _bufferSize the size of the buffer that will be used to return records
     */
    DeviceProvider(shared_ptr<IODevice> _device, int _bufferSize);
    /**
     * Returns a record until the end of the file has been reached
     * It will write an error message to cerr if only a partial record is read as the final read and return a null pointer
     * @return a record from a file or a null pointer if the end of the file has been reached/an error occurred
     */
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
    /**
     * Class constructor that automatically drops the first record
     * @param givenSource the provider to obtain records from
     */
    DropFirst(shared_ptr<Provider> _source);
    /**
     * Gets the next record from the provider if it exists
     * @return a pointer to the next record or a null pointer if a next record does not exist
     */
    shared_ptr<Record> next() override; // see Provider

private:
    shared_ptr<Provider> source;        // the source used to get the records
};

