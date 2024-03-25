#include "RemoveDuplicates.h"
#include <iostream>

RemoveDuplicates::RemoveDuplicates(std::string inputFile, std::string outputFile) {
    this->inputFile = inputFile;
    this->outputFile = outputFile;
}

void RemoveDuplicates::removeDuplicates() {
    ifstream readInput(inputFile);
    if (!readInput) {
        cerr << "The input file could not be opened" << endl;
        return;
    }

    ofstream writeNewOutput(outputFile);
    if (!writeNewOutput) {
        cerr << "The output file could not be opened" << std::endl;
        readInput.close();
        return;
    }

    string record;
    string previousRecord = "";
    while (getline(readInput, record)) {
        if (previousRecord == record){
            previousRecord = record;
            continue;
        } else{
            previousRecord = record;
            writeNewOutput << record << endl;
        }
    }

    readInput.close();
    writeNewOutput.close();
}
