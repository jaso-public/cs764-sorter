#ifndef CS764_SORTER_PRINTER_H
#define CS764_SORTER_PRINTER_H
#include "Provier.h"
#include <string>

/**
 * This class is utilized print out the next record with other information including:
 * - the current time the record was generated
 * - a set message
 * - the record's key (if it is not null)
 * - the record's checksum (if it is not null)
 */
class Printer:Provider {
    // the source to get the next record pointer from
    Provider source;
    // the message to print out with the record
    String message;
    /**
     * Class constructor of the printer
     * @param givenSource given provider to get records from
     * @param givenMessage message to print out with each record
     */
    Printer(Provider givenSource, String givenMessage);
    /*
     * Obtains the next record from the provider with a message
     * If the record is null, it will print out the current time, message, and a null response to console
     * If the record is not null, it will print out the current time, message, record's key, and checksum to console
     * @returns a pointer to the record or a null pointer
     */
    Record* next();
};


#endif //CS764_SORTER_PRINTER_H
