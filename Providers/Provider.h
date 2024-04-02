#ifndef DB_PROVIDER_H
#define DB_PROVIDER_H
#include <stdint.h>
#include "../Records/Record.h"
#include <memory>
using namespace std;


/**
 * This is the provider class that will generate all the desired records
 */
class Provider {

public:
    /**
     * Generates the next record
     * @returns the a pointer to the next record or a null pointer record if the end of the list been reached
     */
    virtual shared_ptr<Record> next() = 0;
};


#endif //DB_PROVIDER_H
