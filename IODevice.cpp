#include "IODevice.h"


/**
 * Class constructor; Opens the given file in read/write mode
 * @param givenFile the string file path of the file
 * Source for exception handling code: https://cplusplus.com/reference/ios/ios/exceptions/
 */
IODevice::IODevice(string filePath){
    fstream f;
    this->streamPtr = &f;
    this->readCount= 0;
    this->readSize = 0;
    this->writeSize = 0;
    this->writeCount = 0;
    // catches exception if file cannot be opened
    (*streamPtr).exceptions ( fstream::failbit);
    try {
        this->file = filePath;
        // opens stream in read/write mode
        (*streamPtr).open(filePath, ios::out | ios::in );
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
    (*streamPtr).exceptions ( fstream ::badbit );
    try {
        // sets file pointer to key location
        (*streamPtr).seekg(offset);
        (*streamPtr).seekg(off);
        // reads bytes of length len and places them into the buffer
        (*streamPtr).read(buffer, len);
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
void IODevice::write(long offset, char * buffer, int off, int len) {
    // catches exception if file cannot be written to
    (*streamPtr).exceptions ( fstream ::badbit );
    try {
        // sets file pointer to key location
        (*streamPtr).seekp(offset);
        (*streamPtr).seekp(off);
        // write bytes of length len and places them into the buffer
        (*streamPtr).write(buffer, len);
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

// closes the stream reading the file
void IODevice::close() {
    // catches exception if file cannot be close
    (*streamPtr).exceptions ( fstream::failbit);
    try {
        // closes stream
        (*streamPtr).close();
    }
    // catches exception when opening file
    catch (fstream ::failure e) {
        cerr << "Error closing: " << file << "\n";
    }
}

// returns a string of read/write statistics
string IODevice::stats() {
    ostringstream oss;
    oss << "read (count=" << readCount <<  " size=" << readSize << ") write(count=" <<  writeCount << ") write(count=" << writeSize << ")";
    return oss.str();
}

// returns the file path and class identification string
string IODevice::toString() {
    ostringstream oss;
    oss << "IoDevice [file=" << file <<  "]";
    return oss.str();
}

int main(){};