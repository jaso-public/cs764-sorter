#include "TestDuplicateRemoval.h"
#include "DuplicateRemoval/RemoveDuplicates.h"

void TestDuplicateRemoval::testRemovingDuplicates1() {
    int recordInFile = 0;
    RemoveDuplicates remove("../Testing/Tests/DuplicateRemoval/input1.txt", "../Testing/Tests/DuplicateRemoval/output1.txt");
    remove.removeDuplicates();
    ifstream checkingOutput("../Testing/Tests/DuplicateRemoval/output1.txt", ios::binary);
    if (!checkingOutput) {
        cerr << "Failed to open output1.txt" << endl;
    }
    string record;
    cout << "Test 1" << "\n";
    while (getline(checkingOutput, record)) {
        cout << record << "\n";
        recordInFile++;
    }
    assert(("Number of expected record in output was not correct" && 4 == recordInFile));
    checkingOutput.close();
}

void TestDuplicateRemoval::testRemovingNoDuplicates2() {
    int recordInFile = 0;
    RemoveDuplicates remove("../Testing/Tests/DuplicateRemoval/input2.txt", "../Testing/Tests/DuplicateRemoval/output2.txt");
    remove.removeDuplicates();
    ifstream checkingOutput("../Testing/Tests/DuplicateRemoval/output2.txt", ios::binary);
    if (!checkingOutput) {
        cerr << "Failed to open output2.txt" << endl;
    }
    string record;
    cout << "Test 2" << "\n";
    while (getline(checkingOutput, record)) {
        cout << record << "\n";
        recordInFile++;
    }
    assert(("Number of expected record in output was not correct" && 6 == recordInFile));
    checkingOutput.close();
}


void TestDuplicateRemoval::testRemovingAllDuplicates3() {
    int recordInFile = 0;
    RemoveDuplicates remove("../Testing/Tests/DuplicateRemoval/input3.txt", "../Testing/Tests/DuplicateRemoval/output3.txt");
    remove.removeDuplicates();
    ifstream checkingOutput("../Testing/Tests/DuplicateRemoval/output3.txt", ios::binary);
    if (!checkingOutput) {
        cerr << "Failed to open output3.txt" << endl;
    }
    string record;
    cout << "Test 3" << "\n";
    while (getline(checkingOutput, record)) {
        cout << record << "\n";
        recordInFile++;
    }
    assert(("Number of expected record in output was not correct" && 1 == recordInFile));
    checkingOutput.close();
}

void TestDuplicateRemoval::testEmptyInputFile4() {
    int recordInFile = 0;
    RemoveDuplicates remove("../Testing/Tests/DuplicateRemoval/input4.txt", "../Testing/Tests/DuplicateRemoval/output4.txt");
    remove.removeDuplicates();
    ifstream checkingOutput("../Testing/Tests/DuplicateRemoval/output4.txt", ios::binary);
    if (!checkingOutput) {
        cerr << "Failed to open output4.txt" << endl;
    }
    string record;
    cout << "Test 4" << "\n";
    while (getline(checkingOutput, record)) {
        cout << record << "\n";
        recordInFile++;
    }
    assert(("Number of expected record in output was not correct" && 0 == recordInFile));
    checkingOutput.close();
}

int main(){
    TestDuplicateRemoval test;
    test.testRemovingDuplicates1();
    test.testRemovingNoDuplicates2();
    test.testRemovingAllDuplicates3();
    test.testEmptyInputFile4();
}