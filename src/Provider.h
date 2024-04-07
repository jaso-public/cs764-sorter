#pragma once

#include <cstdint>
#include <memory>

#include "Record.h"

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
    virtual ~Provider() {}
    virtual shared_ptr<Record> next() = 0;
};
