#include "Consumer.h"


/**
 * Initializes consumer constructor
 * @param givenSource the source to get records from
 */
Consumer::Consumer(Provider* givenSource): source(givenSource)  {}

/**
 * Continues to get records until a null record pointer has been reached
 */
void Consumer::consume() {
    while (true){
        Record* ptr = source->next();
        // if null ptr then end consuming
        if (!ptr){
            return;
        }
    }
}
