#include "IODevice.h"
#include <fstream>
#include <iostream>
using namespace std;

/**
 * Class constructor; Opens the given file in read/write mode
 * @param givenFile the string file path of the file
 * Source for exception handling code: https://cplusplus.com/reference/ios/ios/exceptions/
 */
IODevice::IODevice(string filePath) {
    // catches exception if file cannot be opened
    stream.exceptions ( fstream::failbit);
    try {
        this->file = filePath;
        // opens stream in read/write mode
        stream.open(filePath, ios::out | ios::in );
    }
    // catches exception when opening file
    catch (fstream ::failure e) {
        cerr << "Error opening: " << filePath << "\n";
    }
}

/**
 * Reads a number of bytes from the file at a certain location
 * @param offset the file pointer offset where reading will begin
 * @param buffer place to store read data
 * @param off the location of the first read
 * @param len the number of byes to be read
 */
void IODevice::read(long offset, char * buffer, int off, int len) {
    // catches exception if file cannot be read
    stream.exceptions ( fstream ::badbit );
    try {
        // sets file pointer to key location
        stream.seekg(offset);
        stream.seekg(off);
        // reads bytes of length len and places them into the buffer
        stream.read(buffer, len);
        // increase read count and size
        readCount++;
        readSize+= len;
    }
    // catches failure reading file
    catch (fstream ::failure e) {
        cerr << "Error reading: " << file << " Offset: " << offset << " Buffer length: " << sizeof(buffer) << " Off: " << off << " Len: " << len << "\n";
    }
}

/**
 * Writes a number of bytes from the file at a certain location
 * @param offset the file pointer offset where writing will begin
 * @param buffer place to store written data
 * @param off the location of the first write
 * @param len the number of byes to be written
 */
void IODevice::write(long offset, char *buffer, int off, int len) {
    // catches exception if file cannot be written to
    stream.exceptions ( fstream ::badbit );
    try {
        // sets file pointer to key location
        stream.seekp(offset);
        stream.seekp(off);
        // write bytes of length len and places them into the buffer
        stream.write(buffer, len);
        // increase write count and size
        writeCount++;
        writeSize += len;
    }
    // catches failure writing to file
    catch (fstream ::failure e) {
        cerr << "Error writing: " << file << "\n";
    }
}

// returns the class' read count
long IODevice::getReadCount() {
    return readCount;
}
// returns the class' read size
long IODevice::getReadSize() {
    return readSize;
}

// returns the class' write count
long IODevice::getWriteCount() {
    return writeCount;
}

// returns the class' write size
long IODevice::getWriteSize() {
    return writeSize;
}


