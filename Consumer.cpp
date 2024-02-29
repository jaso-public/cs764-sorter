#include "Consumer.h"
#include "Provider.cpp"

/**
 * Initializes consumer constructor
 * @param givenSource the source to get records from
 */
Consumer::Consumer(Provider givenSource) {
    source = givenSource;
}

/**
 * Continues to get records until a null record pointer has been reached
 */
void Consumer::consume() {
    bool moreRecords = true;
    while (moreRecords){
        Record* ptr = source.next();
        if (ptr == nullptr){
            moreRecords = false;
        }
    }



}

