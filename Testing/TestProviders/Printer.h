#ifndef CS764_SORTER_PRINTER_H
#define CS764_SORTER_PRINTER_H
#include "Providers/Provider.h"
#include <string>
#include <iostream>
#include <sys/time.h>
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
    // the source to get the next record pointer from
    Provider* source;
    // the message to print out with the record
    string message;
    /**
     * Class constructor of the printer that sets the given variables to the class variables
     * @param givenSource given provider to get records from
     * @param givenMessage message to print out with each record
     */
    Printer(Provider* givenSource, string givenMessage);
    /*
     * Obtains the next record from the provider with a message
     * If the record is null, it will print out the current time, message, and a null response to console
     * If the record is not null, it will print out the current time, message, record's key, and checksum to console
     * @returns a pointer to the record or a null pointer
     */
    Record* next() override;
};


#endif //CS764_SORTER_PRINTER_H
