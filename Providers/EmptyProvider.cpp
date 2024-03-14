#include "EmptyProvider.h"

// continues to return a null pointer
Record* EmptyProvider::next() {
    return nullptr;
}
