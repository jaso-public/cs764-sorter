#include "Iterator.h"


Plan::Plan ()
{
	TRACE (true);
} // Plan::Plan

Plan::~Plan ()
{
	TRACE (true);
} // Plan::~Plan


Iterator::Iterator () : _count(0)
{
	TRACE (true);
} // Iterator::Iterator


Iterator::~Iterator ()
{
	TRACE (true);
} // Iterator::~Iterator


// starts the iterator which will continue to generate records until all records have been generated
void Iterator::run ()
{
	TRACE (true);

    // continues to generate records while next has been reached
	while (next ())  ++ _count;

	traceprintf ("entire plan produced %lu rows\n",
			(unsigned long) _count);
} // Iterator::run
