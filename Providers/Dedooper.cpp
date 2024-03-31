#include "Dedooper.h"

Dedooper::Dedooper(Provider *source): source(source) {
    this->previousRecord = nullptr;
}

/**
 * Only returns unique records
 */
Record* Dedooper::next() {
    Record* currentRecord = source->next();
    if (!previousRecord){
        // continues to get next record until a unique record is reached
        while(previousRecord->compareTo(currentRecord) == 0){
            previousRecord = currentRecord;
            currentRecord = source->next();
        }
    }
    return currentRecord;
}



