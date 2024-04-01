#include "SingleProvider.h"

SingleProvider::SingleProvider() {};

/**
    * Sets the class record's variable to the given record
    * @param r the new record variable of the class
 */
void SingleProvider::reset(shared_ptr<Record> r) {
    this->record = r;
}

shared_ptr<Record>  SingleProvider::next() {
    // sets the class' record variable to result to return
    shared_ptr<Record>  result = record;
    // class' record variable turns to null pointer
    this->record = nullptr;
    return result;
}
