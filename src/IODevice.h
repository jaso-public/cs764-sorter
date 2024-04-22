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
    /**
    * Class constructor; Opens the given file in read/write mode
    * @param _filePath the string file path of the file
    * @param _out the stream to display read/write data; if it is a nullptr, then the data will not be displayed
    * Source for exception handling code: https://cplusplus.com/reference/ios/ios/exceptions/
    */
    IODevice(string _filePath, std::ostream* _out);
    IODevice(string _filePath) : IODevice(_filePath, nullptr) {}

    /**
     * Class destructor that will close the file that is being read/written to
     */
    ~IODevice();

    /**
     * Reads a number of bytes from the file at a certain location
     * @param offset the file pointer offset where reading will begin
     * @param buffer place to store read data
     * @param len the number of byes to be read
     */
    int read(uint64_t offset, uint8_t* dst, uint32_t len);
    
    
    /**
     * Writes a number of bytes from the file at a certain location
     * @param offset the file pointer offset where writing will begin
     * @param buffer place to store written data
     * @param off the location of the first write
     * @param len the number of byes to be written
     */
     // TODO get rid of the off (can just send in the right ptr)
    void write(uint64_t offset, uint8_t* src, uint32_t len);

    //TODO: remove flush?
    void flush();
    /**
     * This method will print out statistics from the read/write operations
     * @param out the stream to print the statistics to
     */
    void writeStats(ostream& out);


private:
    std::ostream* out;        // out stream to print io info
    int fd;                   // the file descriptor of the opened device (file)
    string path;              // the path to the device (file name)

    uint64_t readCount;       // number of time read was called
    uint64_t readSize;        // total bytes read from device
    double totalReadSeconds;  // total millis spent reading from the device
    double maxReadSeconds;    // time taken for the longest read operation

    uint64_t writeCount;      // number of time write was called
    uint64_t writeSize;       // total bytes written to device
    double totalWriteSeconds; // total millis spent writing to the device
    double maxWriteSeconds;   // time taken for the longest write operation
};
