#ifndef CS764_SORTER_KEY_H
#define CS764_SORTER_KEY_H


class Key {
public:
    long key;
    long index;
    Key(long key, long index);
    int compareTo(Key other);
};


#endif //CS764_SORTER_KEY_H
