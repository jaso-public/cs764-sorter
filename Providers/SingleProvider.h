#ifndef CS764_SORTER_SINGLEPROVIDER_H
#define CS764_SORTER_SINGLEPROVIDER_H
#include "../Records/Record.h"
#include "Provider.h"

/**
 * This class enables defining and returning a given record
 */
class SingleProvider:Provider {
private:
    // a pointer to a record or a null pointer if the record does not exist
    Record* record;
public:
    /**
     * Sets the class record's variable to the given record
     * @param r the new record variable of the class
     */
    void reset(Record* r);
    // returns the class record's variable and then turns it to null
    Record* next();
};


#endif //CS764_SORTER_SINGLEPROVIDER_H
