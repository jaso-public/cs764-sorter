#include "DropFirst.h"

/**
 * Class constructor that automatically drops the first record
 * @param givenSource the provider to obtain records from
 */
DropFirst::DropFirst(shared_ptr<Provider> _source): source(_source) {
    // sets the given provider to class provider variable and skips first record
    source->next();
}

/**
 * Gets the next record from the provider or a null record
 * @return a pointer to the next record or a null pointer if a next record does not exist
 */
shared_ptr<Record> DropFirst::next() {
    return source->next();
}
