#include "CreateRecords.h"

CreateRecords::CreateRecords(int recordSize, int numberOfRecords) {
    this->recordSize = recordSize;
    this->numberOfRecords = numberOfRecords;
    this->generated = 0;
    this->data = 10;
    write();
}

void CreateRecords::write() {
    // Open file stream for writing
    ofstream outFile("input.txt", std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    while (generated < this->numberOfRecords){
        Record r(10, 8);
        outFile << r.record << std::endl;
        generated++;
    }
    // Close file stream
    outFile.close();
}

void CreateRecords::read() {
    std::ifstream inFile("input.txt", std::ios::binary);
    if (!inFile) {
        cerr << "Failed to open file for reading!" << std::endl;
    }
    // Read and output every piece of data in the file
    std::string data;
    while (inFile >> data) { // Read data until end of file
        cout << data << std::endl; // Output data
    }
    // Close file stream
    inFile.close();
}


int main() {
    // Read object from file
    CreateRecords newObj(10, 10);
    newObj.read();

    return 0;
}