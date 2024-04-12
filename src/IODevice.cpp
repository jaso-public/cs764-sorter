#include "IODevice.h"

#include <cstring>
#include <ctime>
#include <iostream>
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

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    uint32_t count = pread(fd, buffer, len, offset);
    if(count < 0) {
        cerr << "failed reading file:" << path << " strerror:" << strerror(errno) << " errno:" << errno << endl;
        exit(-1);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double duration = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e6;
    readCount++;
    readSize += count;
    totalReadSeconds += duration;
    if(duration > maxReadSeconds) maxReadSeconds = duration;
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

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    uint32_t count = pwrite(fd, src, len, offset);
    if(count != len) {
        cerr << "failed writing file:" << path << " strerror:" << strerror(errno) << " errno:" << errno << endl;
        exit(-1);
   }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double duration = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    writeCount++;
    writeSize += len;
    totalWriteSeconds += duration;
    if(duration > maxWriteSeconds) maxWriteSeconds = duration;
}

void IODevice::writeStats() {
    cout << "Device: " << path << endl;
    cout << "    read" << endl;
    cout << "        count:   " << getReadCount() << " calls" << endl;
    if(getReadCount() > 0) {
        cout << "        size :   " << getReadSize() << " bytes" << endl;
        cout << fixed << setprecision(6) << "        time:    " << getTotalRead() << " seconds" << endl;
        if(getTotalRead()>0) cout << fixed << setprecision(0) << "        average: " << ((double)getReadSize() / getTotalRead()) << " bytes/second" << endl;
        cout << "        maxTime: " << getMaxRead() << " seconds" << endl;
    }
    cout << "    write" << endl;
    cout << "        count:   " << getWriteCount() << " calls" <<endl;
    if(getWriteCount() > 0) {
        cout << "        size :   " << getWriteSize() << " bytes" << endl;
        cout << fixed << setprecision(6) << "        time:    " << getTotalWrite() << " seconds" << endl;
        if (getTotalWrite() > 0)
            cout << fixed << setprecision(0) << "        average: " << ((double) getWriteSize() / getTotalWrite()) << " bytes/second" << endl;
        cout << "        maxTime: " << getMaxWrite() << " second" << endl;
    }
}

uint64_t IODevice::getReadCount() { return readCount; }
uint64_t IODevice::getReadSize() { return readSize; }
double   IODevice::getTotalRead() { return totalReadSeconds; }
double   IODevice::getMaxRead() { return maxReadSeconds; }

uint64_t IODevice::getWriteCount() { return writeCount; }
uint64_t IODevice::getWriteSize() { return writeSize; }
double   IODevice::getTotalWrite() { return totalWriteSeconds; }
double   IODevice::getMaxWrite() { return maxWriteSeconds; }
