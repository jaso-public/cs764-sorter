#ifndef CS764_SORTER_NOOPSORTER_H
#define CS764_SORTER_NOOPSORTER_H
#include "Providers/Provider.h"
using namespace std;


/**
 * A class that implements the provider to return the provider's next record
 */
class NoopSorter: public Provider {
private:
    // the provider that will generate the next record
    Provider* source;
public:
    /**
     * Class constructor that will set the provider
     * @param givenProvider the given provider
     */
    NoopSorter(Provider* givenProvider);
    // returns the provider's next generated record pointer
    Record* next() override;
};


#endif //CS764_SORTER_NOOPSORTER_H
