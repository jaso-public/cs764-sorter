#include "Provider.h"
#include "Record.h"

//TODO: find out to reference the constructor here
Record next(){
    int size = 100;
    uint32_t keyOffset = 8;
    if (numGenerated < numOfRecords){
        Record r =  *new Record(100, keyOffset);
        return r.record;
    }
}
