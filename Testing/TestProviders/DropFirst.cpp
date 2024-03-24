#include "DropFirst.h"
using namespace std;
#include <iostream>

/**
 * Class constructor that automatically drops the first record
 * @param givenSource the provider to obtain records from
 */
DropFirst::DropFirst(Provider givenSource) {
    // sets the given provider to class provider variable and skips first record
    this->source = givenSource;
    source.next();
}

/**
 * Gets the next record from the provider or a null record
 * @return a pointer to the next record or a null pointer if a next record does not exist
 */
Record* DropFirst::next() {
    return source.next();
}

//// main method to make sure drop first is working
//int main(){
//    // create a provider to generate 4 records and passes it to drop first
//    Provider p(4,10,8);
//    DropFirst dropFirst(p);
//
//    // displays all 4 records of the provider
//    cout << "Providers records before drop \n";
//    for (int i = 0; i < 5; i++){
//        Record* ptr = p.next();
//        if (!ptr){
//            cout << "Null pointer was reached\n";
//        } else{
//            Record r = *ptr;
//            cout << r.record << "\n";
//        }
//    }
//    cout << "Providers records with drop \n";
//    // checks that all 4 records are generated then null pointer is reached
//    for (int i = 0; i < 5; i++){
//        Record* ptr = dropFirst.next();
//        if (!ptr){
//            cout << "Null pointer was reached\n";
//        } else{
//            Record r = *ptr;
//            cout << r.record << "\n";
//        }
//    }
//}

int main(){};