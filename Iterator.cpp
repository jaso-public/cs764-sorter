#include "Iterator.h"
#include "Record.cpp"

Plan::Plan ()
{
	TRACE (true);
} // Plan::Plan

Plan::~Plan ()
{
	TRACE (true);
} // Plan::~Plan

//TODO: this needs to be replaced with actual desired number of total records and size
Iterator::Iterator () : _count(0), _totalRecordsCount(200), _sizeOfRecord(10)
{
	TRACE (true);
} // Iterator::Iterator


Iterator::~Iterator ()
{
	TRACE (true);
} // Iterator::~Iterator

/**
 * This method will return true or false is another record should be generated
 * @return true if another record should be generated; else false
 */
bool Iterator::next(){
    while (_totalRecordsCount <  _count){
        //TODO: do something with this created record
        createRecord(_sizeOfRecord);
        return true;
    }
    return false;
}

// starts the iterator which will continue to generate records until all records have been generated
void Iterator::run ()
{
	TRACE (true);

    // continues to generate records while next has been reached
	while (next ())  ++ _count;

	traceprintf ("entire plan produced %lu rows\n",
			(unsigned long) _count);
} // Iterator::run
