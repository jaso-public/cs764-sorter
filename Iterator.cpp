#include "Iterator.h"

/**
 * This class will be utilized it iteratively generate individual records
 * This class will contain a next method that will return the next record, or null if count has been exceeded
 */

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

void Iterator::run ()
{
	TRACE (true);

	while (next ())  ++ _count;

	traceprintf ("entire plan produced %lu rows\n",
			(unsigned long) _count);
} // Iterator::run
