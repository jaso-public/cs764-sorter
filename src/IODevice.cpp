#include "IODevice.h"

#include <cstring>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <fcntl.h>  // Include for open() function
#include <unistd.h> // Include for close() function


/**
 * Class constructor; Opens the given file in read/write mode
 * @param givenFile the string file path of the file
 * Source for exception handling code: https://cplusplus.com/reference/ios/ios/exceptions/
 */
IODevice::IODevice(string filePath) {
    path = filePath;
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
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t count = pread(fd, buffer, len, offset);
    if(count < 0) {
        cerr << "failed reading file:" << path << " strerror:" << strerror(errno) << " errno:" << errno << endl;
        exit(-1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    double elapsed = duration.count();
    elapsed = elapsed / 1e9;

    readCount++;
    readSize += count;
    totalReadSeconds += elapsed;
    if(elapsed > maxReadSeconds) maxReadSeconds = elapsed;
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

    auto start = std::chrono::high_resolution_clock::now();

    uint32_t count = pwrite(fd, src, len, offset);
    if(count != len) {
        cerr << "failed writing file:" << path << " strerror:" << strerror(errno) << " errno:" << errno << endl;
        exit(-1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    double elapsed = duration.count();
    elapsed = elapsed / 1e9;

    writeCount++;
    writeSize += len;
    totalWriteSeconds += elapsed;
    if(elapsed > maxWriteSeconds) maxWriteSeconds = elapsed;
}

void IODevice::writeStats(std::ostream& out) {
    out << "Device: " << path << endl;
    out << "    read" << endl;
    out << "        count:   " << getReadCount() << " calls" << endl;
    if(getReadCount() > 0) {
        out << "        size :   " << getReadSize() << " bytes" << endl;
        out << fixed << setprecision(6) << "        time:    " << getTotalRead() << " seconds" << endl;
        if(getTotalRead()>0) out << fixed << setprecision(0) << "        average: " << ((double)getReadSize() / getTotalRead()) << " bytes/second" << endl;
        out << "        maxTime: " << getMaxRead() << " seconds" << endl;
    }
    out << "    write" << endl;
    out << "        count:   " << getWriteCount() << " calls" <<endl;
    if(getWriteCount() > 0) {
        out << "        size :   " << getWriteSize() << " bytes" << endl;
        out << fixed << setprecision(6) << "        time:    " << getTotalWrite() << " seconds" << endl;
        if (getTotalWrite() > 0) out << fixed << setprecision(0) << "        average: " << ((double) getWriteSize() / getTotalWrite()) << " bytes/second" << endl;
        out << "        maxTime: " << getMaxWrite() << " second" << endl;
    }
}


uint64_t IODevice::get_tsc() {
    uint32_t lo, hi;
    // Inline assembly to read TSC
    __asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}


uint64_t IODevice::getReadCount() { return readCount; }
uint64_t IODevice::getReadSize() { return readSize; }
double   IODevice::getTotalRead() { return totalReadSeconds; }
double   IODevice::getMaxRead() { return maxReadSeconds; }

uint64_t IODevice::getWriteCount() { return writeCount; }
uint64_t IODevice::getWriteSize() { return writeSize; }
double   IODevice::getTotalWrite() { return totalWriteSeconds; }
double   IODevice::getMaxWrite() { return maxWriteSeconds; }
