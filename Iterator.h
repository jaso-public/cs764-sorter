#pragma once

#include "defs.h"

typedef uint64_t RowCount;

/**
 * The Plan class utilizes the Iterator class
 * It will initialize an Iterator that can be used to obtain records
 */
class Plan
{
	friend class Iterator;
public:
    // TODO: unsure what this plan method will do
	Plan ();
	virtual ~Plan ();
	virtual class Iterator * init () const = 0;
private:
}; // class Plan

/**
 * The Iterator class will be called to generate records of the desired amount and size
 */
class Iterator
{
public:
	Iterator ();
	virtual ~Iterator ();
    // starts the iterator
	void run ();
    // returns true if another record exists or false if it does not
	virtual bool next () = 0;
private:
    // keeps track of the number of rows produced
	RowCount _count;
}; // class Iterator
