#ifndef CS764_SORTER_IODEVICE_H
#define CS764_SORTER_IODEVICE_H
#include <stdio.h>
#include <fstream>
#include <string>
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
    long readCount = 0;
    // keeps track of the number of bytes read
    long readSize = 0;
    // keeps track of how many times the file has been written to
    long writeCount = 0;
    // keeps track of the number of bytes written
    long writeSize = 0;

public:
    /**
    * Class constructor; Opens the given file in read/write mode
    * @param givenFile the string file path of the file
    */
    IODevice(string filePath);
    /**
     * Reads a number of bytes from the file at a certain location
     * @param offset the file pointer offset where reading will begin
     * @param buffer place to store read data
     * @param off the location of the first read
     * @param len the number of byes to be read
     */
    void read(long offset, char *buffer, int off, int len);
    /**
     * Writes a number of bytes from the file at a certain location
     * @param offset the file pointer offset where writing will begin
     * @param buffer place to store written data
     * @param off the location of the first write
     * @param len the number of byes to be written
     */
    void write(long offset, char * buffer, int off, int len);
    // returns the class' read count
    long getReadCount();
    // returns the class' read size
    long getReadSize();
    // returns the class' write count
    long getWriteCount();
    // returns the class' write size
    long getWriteSize();
    // closes the stream reading the file
    void close();
    // returns a string of read/write statistics
    string stats();
    // returns the file path and class identification string
    string toString();
};


#endif //CS764_SORTER_IODEVICE_H
