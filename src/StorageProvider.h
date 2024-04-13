#pragma once

#include "Record.h"
#include "Provider.h"

#include "IODevice.h"

/**
 * A configuration class that sets values for the Storage Provider class
 */
class StorageConfig {
public:
    StorageConfig() {}             // Class constructor to initialize class

    uint64_t recordCount;          // the total number of records to be returned
    uint64_t startOffset;          // starting location in storage buffer

    uint8_t *buffer;               // IO buffer
    uint32_t bufferLength;         // size of IO buffer

    shared_ptr<IODevice> storage;  // IO device to read and write from storage
};

/**
 * This class is used to read chunks from the SSD
 */
class StorageProvider: public Provider{
public:
    /**
     * Class constructor
     * @param cfg the configuration file
     */
    StorageProvider(unique_ptr<StorageConfig> &cfg);
    /**
     * Gets the next record from the SSD chunk
     * @returns a pointer to the next record or a null pointer if a next record doesn't exist
     */
    shared_ptr<Record> next() override;

private:
    shared_ptr<StorageConfig> cfg; // configuration file

    int bufferOffset;              // current location in buffer
    int bufferRemaining;           // sum of unread bytes in buffer

    long storageOffset;            // current location in SSD chunk
    long storageRemaining;         // current size of SSD chunk remaining

    long totalRecordsReturned;     // total number of records returned by next() at the current point in time
};
