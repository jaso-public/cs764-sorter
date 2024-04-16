#include "./src/tools/Generate.h"
#include "./src/tools/SortMain.h"

#include <string>
using namespace std;


void testGenerate(int recordSize, int recordCount, double probability, int range, string inputFile) {
        const char* generateArgs[] = {"generate", "-s", nullptr,"-c", nullptr, "-f", nullptr, "-p", nullptr, "-r", nullptr};
        generateArgs[2] = to_string(recordSize).c_str();
        generateArgs[4] = to_string(recordCount).c_str();
        generateArgs[6] = inputFile.c_str();
        generateArgs[8] = to_string(probability).c_str();
        generateArgs[10] = to_string(range).c_str();
        int generateArgsCount = sizeof(generateArgs) / sizeof(generateArgs[0]);
        generateMain(generateArgsCount, const_cast<char**>(generateArgs));
}

void testSort(int recordSize, string inputFile){
    string outFile = "test-output.txt";
    string ssdStagingFile = "test-ssd-staging.txt";
    string hddStagingFile = "test-hdd-staging.txt";
    const char* sortArgs[] = {"sort", "-i", nullptr, "-j", nullptr, "-d", nullptr, "-h", nullptr, "-s", nullptr, "-j", nullptr, "-d", nullptr, "-h", nullptr, "-s", nullptr, "-i", nullptr};
    sortArgs[12] = outFile.c_str();
    sortArgs[14] = ssdStagingFile.c_str();
    sortArgs[16] = hddStagingFile.c_str();
    sortArgs[18] = to_string(recordSize).c_str();
    sortArgs[20] = inputFile.c_str();
    int sortArgsCount = sizeof(sortArgs) / sizeof(sortArgs[0]);
    sortMain(sortArgsCount,const_cast<char**>(sortArgs));
    remove(inputFile.c_str());
    remove(outFile.c_str());
    remove(ssdStagingFile.c_str());
    remove(hddStagingFile.c_str());
}

int main(){
    testGenerate(20, 100, 0.01, 999, "hey-input.txt");
    testSort( 20, "hey-input.txt");
}