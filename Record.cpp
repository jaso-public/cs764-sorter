using namespace std;
#include <iostream>
#include "rng.cpp"

/**
 * This method will create a record in memory and fill it with random 64 bit integers
 * @param size the size of the record
 * @return void* array as the created record
 */
void* createRecord(int size){
    void* record = malloc(size);
    fill(size, record);
    return record;
}

/**
 * This method will calculate the ones complement of a given key
 * @param key a binary representation of a record key as a string
 * @return string of the ones complement version of the key
 * Taken from: https://www.geeksforgeeks.org/c-c-program-to-implement-checksum/
 */
string getOnesComplement(string key)
{
    for (int i = 0; i < key.length(); i++) {
        if (key[i] == '0')
            key[i] = '1';
        else
            key[i] = '0';
    }
    return key;
}

/**
 * This method obtains the key from a given record
 * @param record the record to get the key from
 * @param keyOffset the offset value used to find the key location
 * @return record's key
 */
uint64_t getRecordKey(void* record, uint32_t keyOffset){
    uint64_t* p = (uint64_t*) record;
    uint64_t* keyLocation = p + keyOffset;
    uint64_t key = *keyLocation;
    return key;
}

/**
 * This method will compute a checksum on a record's key
 * @param record is a record
 * @param keyOffset the offset value of key used to define how many blocks of data the binary record will be divded into
 * @return the checksum value of the record
 * https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting was used for the binary conversion
 * https://www.geeksforgeeks.org/c-c-program-to-implement-checksum/ was utilized for the checksum algorithm
*/
string getChecksum(void* record, uint32_t keyOffset){
    // obtain key
    uint64_t key = getRecordKey(record, keyOffset);
    // converts key into binary representation
    string binary = bitset<64>(key).to_string();
    // divide binary value into 8 blocks of 8 bits
    string tempCheckSum = "";
    // first 8 bits
    for (int i = 0; i < keyOffset; i++) {
        tempCheckSum += binary[i];
    }
    // loops through all 8 blocks and adds them together
    for (int i = keyOffset; i < binary.length(); i += keyOffset) {
        // obtains next 8 bits
        string next8Bits = "";
        for (int j = i; j < i + keyOffset; j++) {
            next8Bits += binary[j];
        }
        // Stores the binary addition of tempCheckSum and next8Bits
        string blockAddition = "";
        int sum = 0, carry = 0;
        for (int k = keyOffset - 1; k >= 0; k--) {
            sum += (next8Bits[k] - '0')
                   + (tempCheckSum[k] - '0');
            carry = sum / 2;
            if (sum == 0) {
                blockAddition = '0' + blockAddition;
                sum = carry;
            }
            else if (sum == 1) {
                blockAddition = '1' + blockAddition;
                sum = carry;
            }
            else if (sum == 2) {
                blockAddition = '0' + blockAddition;
                sum = carry;
            }
            else {
                blockAddition = '1' + blockAddition;
                sum = carry;
            }
        }
        // catches and handles a carry of 1 due to binary addition
        string result = "";
        if (carry == 1) {
            for (int l = blockAddition.length() - 1; l >= 0;
                 l--) {
                if (carry == 0) {
                    result = blockAddition[l] + result;
                }
                else if (((blockAddition[l] - '0') + carry) % 2
                         == 0) {
                    result = "0" + result;
                    carry = 1;
                }
                else {
                    result = "1" + result;
                    carry = 0;
                }
            }
            tempCheckSum = result;
        }
        else {
            tempCheckSum = blockAddition;
        }
    }
    // Return One's complements of result value
    // which represents the required checksum value
    return getOnesComplement(tempCheckSum);
}

/**
 * This method will if r1's key is the same as r2's to ensure that the key did not change during sort
 * @param r1 the record prior to manipulation
 * @param r2 the record after manipulation
 * @param keyOffset the offset value used to find the key location
 * @returns true if r2 checksum is 0; else returns false
 */
bool completeChecksumCheck(void* r1, void* r2, uint32_t keyOffset)
{
    // gets the checksum value of each record
    string r1CheckSum= getChecksum(r1, keyOffset);
    string r2CheckSum = getChecksum(r2, keyOffset);
    // checks r2's checksum
    if (count(r2CheckSum.begin(),r2CheckSum.end(), '0')== keyOffset) {
        return true;
    }
    else {
        return false;
    }
}

/**
  * This method compares two records' keys to see which one is greater
   * @param r1 is the first record for comparison
   * @param r2 is the second record for comparison
   * @returns 1 if r1's key > r2's key2, -1 if r1's key1 < r2's key2, or 0 if both keys are equal
  */
  //TODO: decide if we want to only allow keys to be integers as compare() is for strings
int compareRecordKeys(void* r1, void* r2, uint32_t keyOffset){
    // obtains key for each record
    uint64_t key1 = getRecordKey(r1, keyOffset);
    uint64_t key2 = getRecordKey(r2, keyOffset);
    // compares keys to return comparison value
    if (key1 > key2){
        return 1;
    } else if (key1 < key2){
        return -1;
    } else {
        return 0;
    }
}

/**
 * Used for testing purposes
 */
int main(){
    // creates a record of size 100
    int size = 100;
    uint32_t keyOffset = 8;
    // calculates expected chunks
    int chunksInArray = ceil(size/keyOffset);
    uint64_t* recordPointer1 = (uint64_t*) createRecord(size);
    //prints out values in created record
    for (int i = 0; i <= chunksInArray; i++){
        std::cout << *(recordPointer1 + (i)) << ", ";
    }
    // displays comparison result for comparing records
    uint64_t* recordPointer2 = (uint64_t*) createRecord(size);
    int comparisonValue1 = compareRecordKeys(recordPointer1, recordPointer2, keyOffset);
    int comparisonValue2 = compareRecordKeys(recordPointer2, recordPointer1, keyOffset);
    cout << "\nfirst value " << comparisonValue1;
    cout << "\nsecond value " << comparisonValue2;
    string sent_message
            = "10000101011000111001010011101101";
    string recv_message
            = "10000101011000111001010011101101";
    int block_size = 8;

    if (completeChecksumCheck(recordPointer1,
                              recordPointer1,
                block_size)) {
        cout << "No Error";
    }
    else {
        cout << "Error";
    }

    return 0;
}