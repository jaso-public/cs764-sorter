#ifndef CS764_SORTER_DEDOOPER_H
#define CS764_SORTER_DEDOOPER_H

#include "../src/Provider.h"
#include <memory>
using namespace std;


class Dedooper: public Provider {
public:
    Dedooper(shared_ptr<Provider> source): source(source), previousRecord(nullptr) {}

    shared_ptr<Record> next() override {
        auto currentRecord = source->next();
        if (currentRecord == nullptr) return nullptr;

        if (previousRecord != nullptr){
            // continues to get next record until a unique record is reached
            while(currentRecord->isDuplicate(previousRecord)){
                currentRecord = source->next();
                if (currentRecord == nullptr) return nullptr;
            }
        }
        previousRecord = currentRecord;
        return currentRecord;
    }

private:
    shared_ptr<Provider> source;
    shared_ptr<Record> previousRecord;
};

#endif //CS764_SORTER_DEDOOPER_H