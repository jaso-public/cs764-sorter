#include "RemoveDuplicates.h"
#include <iostream>

RemoveDuplicates::RemoveDuplicates(std::string inputFile, std::string outputFile) {
    this->inputFile = inputFile;
    this->outputFile = outputFile;
}

void RemoveDuplicates::removeDuplicates() {
    ifstream readOutput(inputFile);
    if (!readOutput) {
        cerr << "The input file could not be opened" << endl;
        return;
    }

    ofstream writeNewOutput(outputFile);
    if (!writeNewOutput) {
        cerr << "The output file could not be opened" << std::endl;
        readOutput.close();
        return;
    }

    string record;
    string previousRecord = "";
    while (getline(readOutput, record)) {
        if (previousRecord == record){
            previousRecord = record;
            continue;
        } else{
            previousRecord = record;
            writeNewOutput << record << endl;
        }
    }

    readOutput.close();
    writeNewOutput.close();
}
