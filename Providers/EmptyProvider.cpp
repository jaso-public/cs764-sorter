#include "EmptyProvider.h"

EmptyProvider::EmptyProvider() {}

// continues to return a null pointer
shared_ptr<Record> EmptyProvider::next() {
    return nullptr;
}