#ifndef CS764_SORTER_KEY_H
#define CS764_SORTER_KEY_H


#include <cstdint>

class Key {
public:
    uint64_t key;
    long index;
    Key(uint64_t key, long index);
    uint64_t compareTo(Key other);
};


#endif //CS764_SORTER_KEY_H
