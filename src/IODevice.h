#ifndef CS764_SORTER_IODEVICE_H
#define CS764_SORTER_IODEVICE_H
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
private:
    // stream to read/write to file
    fstream* streamPtr;
    // the file to read and write to
    string file;
    // keeps track of how many times the file has been read
    long readCount;
    // keeps track of the number of bytes read
    long readSize;
    // keeps track of how many times the file has been written to
    long writeCount;
    // keeps track of the number of bytes written
    long writeSize;

public:
    ~IODevice();
    /**
    * Class constructor; Opens the given file in read/write mode
    * @param givenFile the string file path of the file
    */
    IODevice(string filePath);
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
    // returns the class' read count
    long getReadCount();
    // returns the class' read size
    long getReadSize();
    // returns the class' write count
    long getWriteCount();
    // returns the class' write size
    long getWriteSize();
    // returns a string of read/write statistics
    string stats();
    // returns the file path and class identification string
    string toString();
};


#endif //CS764_SORTER_IODEVICE_H
