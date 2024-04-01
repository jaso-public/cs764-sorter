#ifndef CS764_SORTER_SINGLEPROVIDER_H
#define CS764_SORTER_SINGLEPROVIDER_H
#include "../Records/Record.h"
#include "Provider.h"
#include "Config/SorterConfig.h"

/**
 * This class enables defining and returning a given record
 */
class SingleProvider: public Provider {
private:
    // a pointer to a record or a null pointer if the record does not exist
    shared_ptr<Record> record;
    SorterConfig cfg;

public:
    SingleProvider(SorterConfig cfg);
    /**
     * Sets the class record's variable to the given record
     * @param r the new record variable of the class
     */
    void reset(shared_ptr<Record> r);
    // returns the class record's variable and then turns it to null
    shared_ptr<Record> next() override;
};


#endif //CS764_SORTER_SINGLEPROVIDER_H
