#include "IODevice.h"

#include <cstring>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <fcntl.h>  // Include for open() function
#include <unistd.h> // Include for close() function


/**
* Class constructor; Opens the given file in read/write mode
* @param _filePath the string file path of the file
* @param _out the stream to display read/write data; if it is a nullptr, then the data will not be displayed
* Source for exception handling code: https://cplusplus.com/reference/ios/ios/exceptions/
*/
IODevice::IODevice(string _filePath, std::ostream* _out) {
    out = _out;
    path = _filePath;
    readCount = 0;
    readSize= 0;
    totalReadSeconds= 0.0;
    maxReadSeconds= 0.0;
    writeCount= 0;
    writeSize= 0;
    totalWriteSeconds= 0.0;
    maxWriteSeconds= 0.0;

    fd = open(path.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd == -1) {
        cerr << "failed opening file:" << path << " strerror:" << strerror(errno) << " errno:" << errno << endl;
        exit(-1);
    }

}

/**
 * Class destructor that will close the file that is being read/written to
*/
IODevice::~IODevice() {
    if(fd < 0) return;

    int result = close(fd);
    fd = -1;
    if(result < 0) {
        cerr << "failed closing file:" << path << " strerror:" << strerror(errno) << " errno:" << errno << endl;
        exit(-1);
    }
}

/**
 * Reads a number of bytes from the file at a certain location
 * @param offset the file pointer offset where reading will begin
 * @param buffer place to store read data
 * @param len the number of byes to be read
 */
int IODevice::read(uint64_t offset, uint8_t* buffer, uint32_t len) {
    auto start = chrono::high_resolution_clock::now();

    uint32_t count = pread(fd, buffer, len, offset);
    if(count < 0) {
        cerr << "failed reading file:" << path << " strerror:" << strerror(errno) << " errno:" << errno << endl;
        exit(-1);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double elapsed = duration.count();
    elapsed = elapsed / 1e9;

    readCount++;
    readSize += count;
    totalReadSeconds += elapsed;
    if(elapsed > maxReadSeconds) maxReadSeconds = elapsed;

    if(out!= nullptr) *out << "read " << path << " offset:" << offset << " length:" << len
        << " call:" << readCount << " bytesRead:" << count
        << " duration:" << fixed << setprecision(6) << elapsed << endl;

    return count;
}


/**
 * Writes a number of bytes from the file at a certain location
 * @param offset the file pointer offset where writing will begin
 * @param buffer place to store written data
 * @param len the number of byes to be written
 */
void IODevice::write(uint64_t offset, uint8_t* src, uint32_t len) {

    if(len == 0) return;

    auto start = chrono::high_resolution_clock::now();

    uint32_t count = pwrite(fd, src, len, offset);
    if(count != len) {
        cerr << "failed writing file:" << path << " strerror:" << strerror(errno) << " errno:" << errno << endl;
        exit(-1);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double elapsed = duration.count();
    elapsed = elapsed / 1e9;

    writeCount++;
    writeSize += len;
    totalWriteSeconds += elapsed;
    if(elapsed > maxWriteSeconds) maxWriteSeconds = elapsed;

    if(out!= nullptr) *out << "write " << path << " offset:" << offset << " length:" << len
    << " call:" << writeCount
    << " duration:" << fixed << setprecision(6) << elapsed << endl;
}

/**
 * This method will print out statistics from the read/write operations
 * @param out the stream to print the statistics to
 */
void IODevice::writeStats(ostream& out) {
    out << "Device: " << path << endl;

    if(readCount + writeCount == 0) {
        out << "    never accessed" << endl;
    }

    if(readCount > 0) {
        out << "    read" << endl;
        out << "        count        : " << readCount << " calls" << endl;
        out << "        size         : " << readSize << " bytes" << endl;
        out << fixed << setprecision(6) << "        time         : " << totalReadSeconds << " seconds" << endl;
        if(totalReadSeconds>0) out << fixed << setprecision(0) << "        average      : " << ((double)readSize / totalReadSeconds) << " bytes/second" << endl;
        out << fixed << setprecision(6) << "        maxTime      : " << maxReadSeconds << " seconds" << endl;
    }

    if(writeCount > 0) {
        out << "    write" << endl;
        out << "        count        : " << writeCount << " calls" <<endl;
        out << "        size         : " << writeSize << " bytes" << endl;
        out << fixed << setprecision(6) << "        time         : " << totalWriteSeconds << " seconds" << endl;
        if (totalWriteSeconds > 0) out << fixed << setprecision(0) << "        average      : " << ((double) writeSize / totalWriteSeconds) << " bytes/second" << endl;
        out << fixed << setprecision(6) << "        maxTime      : " << maxWriteSeconds << " seconds" << endl;
    }
}
