#include "Iterator.h"

Plan::Plan ()
{
	TRACE (true);
} // Plan::Plan

Plan::~Plan ()
{
	TRACE (true);
} // Plan::~Plan

Iterator::Iterator () : _count (0)
{
	TRACE (true);
} // Iterator::Iterator

Iterator::~Iterator ()
{
	TRACE (true);
} // Iterator::~Iterator

// starts the iterator
void Iterator::run ()
{
    //TODO: call the record class to generate the necessary set of records
    //TODO: implement next class to return another record
	TRACE (true);

	while (next ())  ++ _count;

	traceprintf ("entire plan produced %lu rows\n",
			(unsigned long) _count);
} // Iterator::run
