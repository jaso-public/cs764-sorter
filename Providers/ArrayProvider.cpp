#include "ArrayProvider.h"
#include <string>
#include<iterator>
#include<vector>
#include "Records/Record.h"
using namespace std;

/**
 * Array provider constructor
 * @param givenName name to identify the given array iterator
 * @param givenRecords a vector of records
 */
ArrayProvider::ArrayProvider(std::string givenName, vector<Record> givenRecords) {
    // stores give variables as class variables
    this->name = givenName;
    this->records = givenRecords;
    // places pointer at start of records vector
    this->ptr = records.begin();

}

/**
 * Continues to return the next method while one exists
 * @return a pointer to the next record or a null pointer if the next record does not exist
 */
Record* ArrayProvider::next() {
    // checks that another record exists
    if (ptr < records.end()){
        // create a temporary ptr to allow ptr to increment
        vector<Record>::iterator tempPtr = ptr;
        // ptr points to next Record if it exists
        ptr++;
        // create a pointer to the returned record
        Record result = *tempPtr;
        Record* recordPtr =  &result;
        return recordPtr;
    }
    return nullptr;
}

////main method to ensure that this method is working properly
//int main(){
//    // creating a vector with size 3
//    Record r(10, 10);
//    vector<Record> recordVector(3);
//    fill(recordVector.begin(), recordVector.end(), r);
//
//
//    // should return 3 records before returning a null pointer
//    ArrayProvider provider("test",recordVector);
//    for(int i = 0; i < 4; i++){
//        Record* next = provider.next();
//        if (next){
//            Record r = *next;
//            cout << r.record << " ";
//        } else{
//            cout << "null pointer reached";
//        }
//    }
//}
