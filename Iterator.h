#pragma once

#include "defs.h"

typedef uint64_t RowCount;

/**
 * The Plan class utilizes the Iterator class
 */
class Plan
{
	friend class Iterator;
public:
    // TODO: plan method will call the record class to obtain the necessary amount of records?
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
    // TODO: run method will continue to obtain new records until all have been obtained
	void run ();
	virtual bool next () = 0;
private:
	RowCount _count;
}; // class Iterator
