#ifndef CS764_SORTER_EMPTYPROVIDER_H
#define CS764_SORTER_EMPTYPROVIDER_H
#include "../Records/Record.h"
#include "Provider.h"

/**
 * This class is an empty provider that continues to return a null pointer as a record
 */
class EmptyProvider: public Provider {
public:
    // continues to return a null pointer
    shared_ptr<Record> next() override;
    EmptyProvider();
};


#endif //CS764_SORTER_EMPTYPROVIDER_H
