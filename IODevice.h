#ifndef CS764_SORTER_IODEVICE_H
#define CS764_SORTER_IODEVICE_H
#include <stdio.h>
#include <fstream>

/**
 * This class it utilized to read and write to a given file
 */
class IODevice {
private:
    // the file to read and write to
    FILE * file;
    // keeps track of how many times the file has been read
    long readCount = 0;
    // keeps track of the number of bytes read
    long readSize = 0;
    // keeps track of how many times the file has been written to
    long writeCount = 0;
    // keeps track of the number of bytes written
    long writeSize = 0;

public:
    /*
     * Class constructor that initializes a stream to the given file
     * @param givenFile is the file location to read and write to
     */
    IODevice(* givenFile);
    /**
     * Reads a number of bytes from the file at a certain location
     * @param offset the file pointer offset where reading will begin
     * @param buffer place to store read data
     * @param off the location of the first read
     * @param len the number of byes to be read
     */
    void read(long offset, void* buffer, int off, int len);
    /**
     * Writes a number of bytes from the file at a certain location
     * @param offset the file pointer offset where writing will begin
     * @param buffer place to store written data
     * @param off the location of the first write
     * @param len the number of byes to be written
     */
    void write(long offset, void* buffer, int off, int len);
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
};


#endif //CS764_SORTER_IODEVICE_H
