#ifndef CS764_SORTER_DROPFIRST_H
#define CS764_SORTER_DROPFIRST_H
#include "Provider.h"
#include "Records/Record.h"

/**
 * This class is utilized to automatically skip the first record and return all other records
 * The next() method can be called to generate the next record
 */
class DropFirst {
public:
    // the source used to get the records
    Provider source;
    // class constructor
    DropFirst(Provider givenSource);
    /**
     * Gets the next record from the provider or a null record
     * @return a pointer to the next record or a null pointer if a next record does not exist
     */
    Record* next();
};


#endif //CS764_SORTER_DROPFIRST_H
