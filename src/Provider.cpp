#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "Provider.h"


FileProvider::FileProvider(string filePath) {
    eofReached = false;
    fd = open(filePath.c_str(), O_RDONLY);
    if (fd == -1) {
        cerr << "error opening file:" << filePath << " errno:" << errno << " " << strerror(errno) << endl;
        exit(-1);
    }
}

FileProvider::~FileProvider() {
    if(fd < 0) return;
    int result = close(fd);
    if (result == -1) {
        cerr << "error closingfile:" << filePath << " errno:" << errno << " " << strerror(errno) << endl;
        exit(-1);
    }
    fd = -1;
}

shared_ptr<Record> FileProvider::next() {
    if(eofReached) return nullptr;

    int recordSize = Record::getRecordSize();
    int remaining = recordSize;
    int offset = 0;
    auto buffer = std::make_unique<uint8_t[]>(recordSize);

    while(remaining>0) {
        int count = read(fd, buffer.get() + offset, remaining);
        if (count < 0) {
            cerr << "error reading file:" << filePath << " errno:" << errno << " " << strerror(errno) << endl;
            exit(-2);
        }

        if (count == 0) {
            if (offset != 0) {
                cerr << "partial record at the end of the file:" << filePath << endl;
                exit(-3);
            }
            eofReached = true;
            return nullptr;
        }

        offset += count;
        remaining -= count;
    }

    return make_shared<Record>(buffer);
}

