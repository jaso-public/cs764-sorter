#include "Key.h"

Key::Key(uint64_t key, long index) {
  this->key = key;
  this->index = index;
}

/**
      * This method is utilized to compare a record to another record based on its key or index
      * @param other the other Key to compare to the current Key
      * @return -1 if current key/index is less than other key/index or 1 if current key/index is greater than other key/index
     */
uint64_t Key::compareTo(Key other) {
    if(key < other.key) return -1;
    if(key > other.key) return +1;
    // if keys are the same, then compares indexes
    if(index < other.index) return -1;
    if(index > other.index) return +1;
    return 0;
}
