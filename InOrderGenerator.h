#ifndef CS764_SORTER_INORDERGENERATOR_H
#define CS764_SORTER_INORDERGENERATOR_H
#include "Provider.h";
#include <stdlib.h>

/**
 * This class can be used to generate records of a certain size and amount
 */
class InOrderGenerator:Provider {
public:
    // represents total number of records to generate
    long count;
    // represents the size of the records
    int size;
    // class constructor
    InOrderGenerator(long givenCount, int givenSize);\
    // returns a pointer to the next record or a null pointer if a next record does not exist
    Record* next();
private:
    // stores actual number of records currently generated
    long generated = 0;
    // random number
    int rng = rand();
};


#endif //CS764_SORTER_INORDERGENERATOR_H
