#ifndef CS764_SORTER_KEY_H
#define CS764_SORTER_KEY_H


#include <cstdint>
#include <iostream>
using namespace std;

class Key {
public:
    uint64_t key;
    long index;
    Key(uint64_t key, long index);
    uint64_t compareTo(Key other);

    // these are required to have the mapping in tree sorter work
    bool operator<(const Key& other) const{
        return key < other.key;
    }

    bool operator==(const Key& other) const{
        return key == other.key;
    }
};


#endif //CS764_SORTER_KEY_H
