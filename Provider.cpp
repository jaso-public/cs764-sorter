#include "Provider.h"
#include "Record.h"

int size;
uint32_t keyOffset;

Record::Record(int size, uint32_t keyOffset){

}

//TODO: find out to reference the constructor here
Record next(){
    int size = 100;
    uint32_t keyOffset = 8;
    if (numGenerated < numOfRecords){
        Record r =  *new Record(100, keyOffset);
        return r.record;
    }
}
