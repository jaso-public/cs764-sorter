#include "SingleProvider.h"

SingleProvider::SingleProvider() {};

/**
    * Sets the class record's variable to the given record
    * @param r the new record variable of the class
 */
void SingleProvider::reset(Record* r) {
    this->record = r;
}

Record* SingleProvider::next() {
    // sets the class' record variable to result to return
    Record* result = record;
    // class' record variable turns to null pointer
    this->record = nullptr;
    return result;
}

int main(){
    SingleProvider test;
    test.next();
}
