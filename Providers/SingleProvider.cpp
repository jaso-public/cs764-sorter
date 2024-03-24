#include "SingleProvider.h"

/**
    * Sets the class record's variable to the given record
    * @param r the new record variable of the class
 */
void SingleProvider::reset(Record* r) {
    record = r;
}

Record* SingleProvider::next() {
    // sets the class' record variable to result to return
    Record* result = record;
    // class' record variable turns to null pointer
    record = nullptr;
    return result;
}

int main(){};