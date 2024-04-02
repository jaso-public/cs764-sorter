#include "IODevice.h"


/**
 * Class constructor; Opens the given file in read/write mode
 * @param givenFile the string file path of the file
 * Source for exception handling code: https://cplusplus.com/reference/ios/ios/exceptions/
 */
IODevice::IODevice(string filePath){
    this->readCount= 0;
    this->readSize = 0;
    this->writeSize = 0;
    this->writeCount = 0;
    this->file = filePath;
    // opens for reading and writing
    this->streamPtr = new fstream(filePath, ios::in | ios::out);
    if (!streamPtr->is_open()) {
        cerr << "Error opening: " << filePath << "\n";
        delete streamPtr;
        streamPtr = nullptr;
    }
}

IODevice::~IODevice() {
    if (streamPtr) {
        streamPtr->close();
        delete streamPtr;
    }
}

/**
 * Reads a number of bytes from the file at a certain location
 * @param offset the file pointer offset where reading will begin
 * @param buffer place to store read data
 * @param off within the buffer
 * @param len the number of byes to be read
 */
void IODevice::read(long offset, uint8_t* buffer, int off, int len) {
    if (!streamPtr) {
        cerr << "File not open for reading\n";
        return;
    }
    // catches exception if file cannot be read
    (*streamPtr).exceptions ( fstream ::badbit );
    try {
        (*streamPtr).seekg(offset, ios::beg);
        (*streamPtr).read(reinterpret_cast<char*>(buffer + off), len);
        readCount++;
        readSize+= len;
    }
    // catches failure reading file
    catch (ios_base ::failure e) {
        cerr << "Error reading: " << file << " Offset: " << offset << " Off: " << off << " Len: " << len << "\n";
    }
}


/**
 * Writes a number of bytes from the file at a certain location
 * @param offset the file pointer offset where writing will begin
 * @param buffer place to store written data
 * @param off within the buffer
 * @param len the number of byes to be written
 */
void IODevice::write(long offset, uint8_t* buffer, int off, int len) {
    if (!streamPtr) {
        cerr << "File not open for writing\n";
        return;
    }
    // catches exception if file cannot be written to
    (*streamPtr).exceptions ( fstream ::badbit );
    try {
        // sets file pointer to key location
        (*streamPtr).seekp(offset);
        // write bytes of length len and places them into the buffer
        (*streamPtr).write(reinterpret_cast<const char *>(buffer + off), len);
        // increase write count and size
        writeCount++;
        writeSize += len;
    }
    // catches failure writing to file
    catch (ios_base ::failure e) {
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