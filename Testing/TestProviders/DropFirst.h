#ifndef CS764_SORTER_DROPFIRST_H
#define CS764_SORTER_DROPFIRST_H
#include <iostream>

#include "Provider.h"
#include "Record.h"


/**
 * This class is utilized to automatically skip the first record and return all other records
 * The next() method can be called to generate the next record
 */
class DropFirst: public Provider{
public:
    // the source used to get the records
    shared_ptr<Provider> source;
    // class constructor
    DropFirst(shared_ptr<Provider> _source);
    /**
     * Gets the next record from the provider or a null record
     * @return a pointer to the next record or a null pointer if a next record does not exist
     */
    shared_ptr<Record> next() override;
};


#endif //CS764_SORTER_DROPFIRST_H
