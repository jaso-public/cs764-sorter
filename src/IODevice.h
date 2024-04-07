#pragma once

#include <stdio.h>
#include <fstream>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * This class it utilized to read and write to a given file
 */
class IODevice {

public:
    IODevice(string filePath);
    ~IODevice();

    /**
     * Reads a number of bytes from the file at a certain location
     * @param offset the file pointer offset where reading will begin
     * @param buffer place to store read data
     * @param len the number of byes to be read
     */
    void read(long offset, uint8_t* dst, int len);
    
    
    /**
     * Writes a number of bytes from the file at a certain location
     * @param offset the file pointer offset where writing will begin
     * @param buffer place to store written data
     * @param off the location of the first write
     * @param len the number of byes to be written
     */
     // TODO get rid of the off (can just send in the right ptr)
    void write(long offset, uint8_t* dst, int off, int len);

    /**
     * as this IoDevice does I/O operations to and from the device,
     * it records simple statistics about the read and write operations.
     * The methods below should be fairly obvious about what the measurement
     * is recording for each statistic.
     */
    uint64_t getReadCount();     // cumulative numbers of times read was called
    uint64_t getReadSize();      // cumulative numbers of bytes read from this device
    uint64_t getReadMillis();    // cumulative time measured in millis for all read operations 
    uint64_t getMaxReadMillis(); // the elapsed millis of the longest read operation for this device

    uint64_t getWriteCount();     // cumulative numbers of times read was called
    uint64_t getWriteSize();      // cumulative numbers of bytes read from this device
    uint64_t getWriteMillis();    // cumulative time measured in millis for all read operations 
    uint64_t getMaxWriteMillis(); // the elapsed millis of the longest read operation for this device

private:
    int fd;                  // the file descriptor of the opened device (file)
    string pathName;         // the path to the IoDevice (file name)

    uint64_t readCount;      // number of time read was called
    uint64_t readSize;       // total bytes read from device
    uint64_t readMillis;     // total millis spent reading from the device
    uint64_t maxReadMillis;  // time taken for the longest read operation

    uint64_t writeCount;     // number of time write was called
    uint64_t writeSize;      // total bytes written to device
    uint64_t writeMillis;    // total millis spent writing to the device
    uint64_t maxWriteMillis; // time taken for the longest write operation
};
