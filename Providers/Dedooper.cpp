#include "Dedooper.h"

Dedooper::Dedooper(Provider *source): source(source) {
    this->previousRecord = nullptr;
}

/**
 * Only returns unique records
 */
shared_ptr<Record> Dedooper::next() {
    shared_ptr<Record> currentRecord = source->next();
    if (currentRecord == nullptr) return nullptr;
    if (!previousRecord){
        // continues to get next record until a unique record is reached
        while(previousRecord->isDuplicate(currentRecord)){
            previousRecord = currentRecord;
            currentRecord = source->next();
        }
    }
    return currentRecord;
}



