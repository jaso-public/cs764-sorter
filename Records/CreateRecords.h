#ifndef CS764_SORTER_CREATERECORDS_H
#define CS764_SORTER_CREATERECORDS_H
#include <iostream>
#include <fstream>
#include "./Record.h"
using namespace std;

/**
 * This is the provider class that will generate all the desired records
 */
class CreateRecords {

public:
    Record record;
    int recordSize;
    int numberOfRecords;
    int generated;

    CreateRecords(int recordSize, int numberOfRecords){
        this->recordSize = recordSize;
        this->numberOfRecords = numberOfRecords;
        this->generated = 0;
        write();
    }

    void write(){
        // Open file stream for writing
        ofstream outFile("input.txt", std::ios::binary);
        if (!outFile) {
            std::cerr << "Failed to open file for writing!" << std::endl;
        }
        while (generated < numberOfRecords){
            Record r(10, 8);
            outFile << r.record << std::endl;
            generated++;
        }
        // Close file stream
        outFile.close();
    }

    void read(istream & is){
        // Read and output every piece of data in the file
        std::string data;
        while (is >> data) { // Read data until end of file
            std::cout << data << std::endl; // Output data
        }

       // is.read(reinterpret_cast<char*>(&data), sizeof(data));
    }
};

int main() {
    // Open file stream for reading
    std::ifstream inFile("input.txt", std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return 1;
    }

    // Read object from file
    CreateRecords newObj(10, 10);
    newObj.read(inFile);

    // Close file stream
    inFile.close();

    // Output the deserialized object
    std::cout << "Deserialized object: " << record. << std::endl;

    return 0;
}


#endif //CS764_SORTER_CREATERECORDS_H
