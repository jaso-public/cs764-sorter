#include "EmptyProvider.h"

EmptyProvider::EmptyProvider() {}

// continues to return a null pointer
Record* EmptyProvider::next() {
    return nullptr;
}