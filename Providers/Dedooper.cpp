#include "Dedooper.h"

Dedooper::Dedooper(Provider *source): source(source) {
}

//TODO: only return unique records
Record* Dedooper::next() {
    return source->next();
}



