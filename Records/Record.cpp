
#include "Record.h"


/**
 * Initializes record constructor
 * @param sizeFromUser size of record
 * @param keyOffsetFromUser key offset of record
 */
Record::Record(uint64_t sizeFromUser, uint32_t keyOffsetFromUser) {
    this->size = sizeFromUser;
    this->keyOffset = keyOffsetFromUser;
    // creating/setting record and its key
    void* record = malloc(size);
    fill(size, record);
    this->record = record;
    this->key = getRecordKey();
    this->compareCount = 0;
}

Record::Record() {}

/**
 * This method obtains the key from a given record
 * @return record's key
 */
uint64_t Record::getRecordKey(){
    uint64_t* p = (uint64_t*) record;
    uint64_t* keyLocation = p + keyOffset;
    uint64_t key = *keyLocation;
    return key;
}

/**
 * This method will compute the checksum value of a given record
 * @returns the checksum value of the record
 */
uint64_t Record::completeChecksumCheck(){
    int extra = size & 7;
    int num = size >> 3;

    uint64_t result = 0;
    uint64_t *a = (uint64_t*) record;
    for(int i=0; i<num ; i++){
        result = result ^ a[i];
    }

    if(extra) {
        uint64_t tmp = 0;
        void* ending = a + num;
        memcpy(&tmp, ending, extra);
        result ^= tmp;
    }

    return result;
}

/**
   * Compares two records' keys together
   * @param other is the other record to compare keys to the class' record
   * @return 1 if the class key is greater; -1 if the other key is greater
   */
int Record::compareTo(Record other) {
    compareCount++;
    uint64_t classKey = getRecordKey();
    uint64_t otherKey =     other.getRecordKey();
    if (classKey > otherKey){
        return 1;
    } else {
        return -1;
    }
}

/**
 * Sets the compareCount variable back to 0
 */
void Record::resetCompareCount() {
    compareCount = 0;
}

/**
 * @return the compare count variable
 */
long Record::getCompareCount() {
    return compareCount;
}

void Record::store(char *buffer, int offset) {
    void *source = &record;
    void *destination = &buffer + offset;
    memcpy(destination, source, sizeof(buffer));
}

void Record::storePartial(char *buffer, int offset, int start, int length) {
    void *source = &record + start;
    void *destination = &buffer + offset;
    memcpy(destination, source, length);
}
