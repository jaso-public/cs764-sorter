#include "Record.h"

// initialize the global values for the record parameters
uint32_t Record::recordSize = 64;
uint64_t Record::compareCount = 0;

/**
 * Sets the class' static variables
 * @param _recordSize the size of each record
 */
void Record::staticInitialize(uint32_t _recordSize) {
    recordSize = _recordSize;
    compareCount = 0;
}

/**
 * Stores the given record into the class' record variable (data)
 * @param newData given record
 */
Record::Record(unique_ptr<uint8_t[]> &newData) {
    if(newData == nullptr) {
        cerr << "cannot construct a Record with a nullptr" <<endl;
        exit(-1);
    }
    if(newData.get() == nullptr) {
        cerr << "cannot construct a Record with a nullptr" <<endl;
        exit(-1);
    }

    data = std::move(newData);
}

/**
 * This method compares the class' record to the given record (other)
 * @param other the record to compare with the class' record
 * @return 1 if other is smaller than the class' record, 0 if the two records or equal, or false
 */
int Record::compareTo(const shared_ptr<Record> &other) {
    compareCount++;
    return memcmp(this->data.get(), other->data.get(), recordSize);
}

/**
 * This method copies the contents of the record (data) into the specified memory location
 * @param dst the desired location in memory
 */
void Record::store(uint8_t *dst) {
    memcpy(dst, data.get(), recordSize);
}

/**
 * Stores part of the record into the destination array
 * @param dst the destination where the bytes will be stored
 * @param offset the starting offset in the record from where to begin the transfer
 * @param numToCopy the number of bytes to be moved to the destination
*/
void Record::store(uint8_t *dst, int offset, int numToCopy) {
    memcpy(dst, data.get() + offset, numToCopy);
}


/**
 * Prints out the contents and checksum of the record
 * @param message to identify the method call
*/
void Record::dump(string message) {
    cout << message << " ";
    for (int i = 0; i < recordSize; i++) {
        printf("%c", data[i]);
    }
    cout << " checksum:" << checksum() << endl;
}

// TODO compute a real crc32
/**
 * Computes the checksum of the record
 * @return the record's checksum
*/
uint64_t Record::checksum() {
    int extra = recordSize & 7;
    int num = recordSize >> 3;
    uint64_t result = 0;
    uint64_t *a = (uint64_t *) data.get();
    for (int i = 0; i < num; i++) {
        result = result ^ a[i];
    }
    if (extra) {
        uint64_t tmp = 0;
        void *ending = a + num;
        memcpy(&tmp, ending, extra);
        result ^= tmp;
    }
    return result;
}
