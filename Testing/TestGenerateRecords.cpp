#include "./src/tools/GenerateMain.cpp"
#include "./src/tools/SortMain.cpp"

    void testGenerateAndSortRecords(int recordSize, int recordCount, double probability, int range) {
        string inFile = "test-input.txt";
        const char* generateArgs[] = {"generate", "-s", nullptr, "-c", nullptr, "-f", nullptr, "-p", nullptr, "-r", nullptr};
        generateArgs[2] = to_string(recordSize).c_str();
        generateArgs[4] = to_string(recordCount).c_str();
        generateArgs[6] = inFile.c_str();
        generateArgs[8] = to_string(probability).c_str();
        generateArgs[10] = to_string(range).c_str();
        int generateArgsCount = sizeof(generateArgs) / sizeof(generateArgs[0]);
        generateMain(generateArgsCount, const_cast<char**>(generateArgs));

        string outFile = "test-output.txt";
        string ssdStagingFile = "test-ssd-staging.txt";
        string hddStagingFile = "test-hdd-staging.txt";
        const char* sortArgs[] = {"sort", "-s", nullptr, "-i", nullptr, "-j", nullptr, "-d", nullptr, "-h", nullptr};
        sortArgs[2] = to_string(recordSize).c_str();
        sortArgs[4] = inFile.c_str();
        sortArgs[6] = outFile.c_str();
        sortArgs[8] = ssdStagingFile.c_str();
        sortArgs[10] = hddStagingFile.c_str();
        int sortArgsCount = sizeof(sortArgs) / sizeof(sortArgs[0]);
        sortMain(sortArgsCount,const_cast<char**>(sortArgs));

        remove(inFile.c_str());
        remove(outFile.c_str());
        remove(ssdStagingFile.c_str());
        remove(hddStagingFile.c_str());
    }

int main(){
    testGenerateAndSortRecords(20, 100, 0.01, 999);
}