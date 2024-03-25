#include "CreateRecords.h"

CreateRecords::CreateRecords(int recordSize, int numberOfRecords) {
    this->recordSize = recordSize;
    this->numberOfRecords = numberOfRecords;
    this->generated = 0;
}

// will write desired amount of records to input1.txt file
void CreateRecords::write() {
    ofstream outFile("input.txt", ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
    while (generated < numberOfRecords){
        //TODO: record should be able to have alpha chars
        Record r(recordSize, 1);
        outFile << r.record << std::endl;
        generated++;
    }
    // Close file stream
    outFile.close();
}


// this will be the method that each provider can use to return next()
void* CreateRecords::next(istream& is) {
    void* record;
    // checks that next line exists
    if (is >> record) {
        // goes to next record
        is.seekg(1, std::ios_base::cur);
        return record;
    }
    return nullptr;
}


int main() {
    CreateRecords test(8, 4);
    test.write();
    ifstream inFile("input.txt", ios::binary);
    if (!inFile) {
        cerr << "Failed to open file for reading." << std::endl;
    }
    for (int i = 0; i < 5; i++){
      cout <<  test.next(inFile) << "\n";
    }
    // Close file stream
    inFile.close();
}