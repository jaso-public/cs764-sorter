#include "./src/tools/generate.cpp"

    //TODO: I want to call the generator's class' main method, but I need to have a main method in here to run the test
    // I originally put the generator and sort methods into their own class, but we do not want to do this I do not think
    // I didnt change anything in generator.cpp or sort.cpp for this reason
    //TODO: if I import sort.cpp into this file I get an error because of the Convert.h template

    void testGenerateAndSortRecords(int recordSize, int recordCount, double probability, int range) {
        string inFile = "test-input.txt";
        const char* generateArgs[] = {"generate", "-s", nullptr, "-c", nullptr, "-f", nullptr, "-p", nullptr, "-r", nullptr};
        generateArgs[2] = to_string(recordSize).c_str();
        generateArgs[4] = to_string(recordCount).c_str();
        generateArgs[6] = inFile.c_str();
        generateArgs[8] = to_string(probability).c_str();
        generateArgs[10] = to_string(range).c_str();
        int generateArgsCount = sizeof(generateArgs) / sizeof(generateArgs[0]);
        //TODO: I tried to put generator into a class (Generator)
        Generator g;
        g.main(generateArgsCount, const_cast<char**>(generateArgs));

        //TODO: I tried to put sort into a class (Sort)
//        Sort s;
//        string outFile = "test-output.txt";
//        string ssdStagingFile = "test-ssd-staging.txt";
//        string hddStagingFile = "test-hdd-staging.txt";
//        const char* sortArgs[] = {"sort", "-s", nullptr, "-i", nullptr, "-j", nullptr, "-d", nullptr, "-h", nullptr};
//        sortArgs[2] = to_string(recordSize).c_str();
//        sortArgs[4] = inFile.c_str();
//        sortArgs[6] = outFile.c_str();
//        sortArgs[8] = ssdStagingFile.c_str();
//        sortArgs[10] = hddStagingFile.c_str();
//        int sortArgsCount = sizeof(sortArgs) / sizeof(sortArgs[0]);
//        s.main(sortArgsCount,const_cast<char**>(sortArgs));
//

//        remove(outFile.c_str());
//        remove(ssdStagingFile.c_str());
//        remove(hddStagingFile.c_str());
        remove(inFile.c_str());
    }

int main(){
    testGenerateAndSortRecords(20, 100, 0.01, 999);
}