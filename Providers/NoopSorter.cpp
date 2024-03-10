#include "NoopSorter.h"
/**
  * Class constructor that will set the provider
  * @param givenProvider the given provider
  */
NoopSorter::NoopSorter(Provider givenProvider) {
    this->source = givenProvider;
}

// returns the provider's next generated record pointer
Record* NoopSorter::next() {
    return source.next();
}
