#ifndef CS764_SORTER_NOOPSORTER_H
#define CS764_SORTER_NOOPSORTER_H
#include "Providers/Provider.h"
using namespace std;


/**
 * A class that implements the provider to return the provider's next record
 */
class NoopSorter: public Provider {
public:
    NoopSorter(shared_ptr<Provider> source): source(source) {}

    shared_ptr<Record> next() override {
        return source->next();
    }

private:
    shared_ptr<Provider> source; // the provider that will generate the next record
};


#endif //CS764_SORTER_NOOPSORTER_H
