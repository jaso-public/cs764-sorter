#ifndef CS764_SORTER_PRINTER_H
#define CS764_SORTER_PRINTER_H

#include <string>
#include <iostream>
#include <sys/time.h>

#include "Provider.h"

using namespace std;

/**
 * This class is utilized print out the next record with other information including:
 * - the current time the record was generated
 * - a set message
 * - the record's key (if it is not null)
 * - the record's checksum (if it is not null)
 */
class Printer: public Provider {
public:
    Printer(shared_ptr<Provider> _source, string _message): source(_source), message(_message) {}

     /*
     * Obtains the next record from the provider with a message
     * If the record is null, it will print out the current time, message, and a null response to console
     * If the record is not null, it will print out the current time, message, record's key, and checksum to console
     * @returns a pointer to the record or a null pointer
     */
    shared_ptr<Record> next() override;

private:
    shared_ptr<Provider> source; // the source to get the next record pointer from
    string message;              // the message to print out with the record

};


#endif //CS764_SORTER_PRINTER_H
