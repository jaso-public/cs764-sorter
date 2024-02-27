#include "Filter.h"

/**
 * This class is utilized to obtain records and remove duplicate keys within records
 * sets _input to given input value
 * @param input is a Plan class that contains all the generated records
 */
FilterPlan::FilterPlan (Plan * const input) : _input (input)
{
    TRACE (true);
} // FilterPlan::FilterPlan

/**
 * Deletes the set _input value
 */
FilterPlan::~FilterPlan ()
{
    TRACE (true);
    delete _input;
} // FilterPlan::~FilterPlan

/**
 * Create the FilterIterator as a Iterator to start obtaining records
 * @return the FilterIterator
 */
Iterator * FilterPlan::init () const
{
    TRACE (true);
    return new FilterIterator (this);
} // FilterPlan::init


/**
 * Method that will start obtaining records
 * @param plan the FilterPlan that contains all the records
 */
FilterIterator::FilterIterator (FilterPlan const * const plan) :
    _plan (plan), _input (plan->_input->init ()),
    _consumed (0), _produced (0)
{
    TRACE (true);
} // FilterIterator::FilterIterator

FilterIterator::~FilterIterator ()
{
    TRACE (true);

    delete _input;

    traceprintf ("produced %lu of %lu rows\n",
            (unsigned long) (_produced),
            (unsigned long) (_consumed));
} // FilterIterator::~FilterIterator

/**
 * Continues to obtain a new record until all records are obtained
 * @return true indicating another record exists, false if all records have been returned
 */
bool FilterIterator::next ()
{
    TRACE (true);
    //TODO: call the record class to generate the necessary set of records
    //TODO: make this method evaluate to true or false on if a next record class is generated or not

    do
    {
        // assigning value of next to input variable
        // returns false when next if false (no more records to generate)
        if ( ! _input->next ())  return false;
        ++ _consumed;
    } while (_consumed % 2 == 0);

    ++ _produced;
    return true;
} // FilterIterator::next
