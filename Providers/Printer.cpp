#include "Printer.h"
using namespace std;
#include <iostream>
/**
   * Class constructor of the printer that sets the given variables to the class variables
   * @param givenSource given provider to get records from
   * @param givenMessage message to print out with each record
   */
Printer::Printer(int givenSource, std::string givenMessage) {
    this->source = givenSource;
    this->message = message;
}

/*
 * Obtains the next record from the provider with a message
 * If the record is null, it will print out the current time, message, and a null response to console
 * If the record is not null, it will print out the current time, message, record's key, and checksum to console
 * @returns a pointer to the record or a null pointer
 */
//TODO: get current time in miliseconds
Record* Printer::next() {
    Record* recordPtr = source.next();
    // if record pointer is null
    if (!recordPtr){
        cout << " " << message << ": record is null!";
        return recordPtr;
    }
    Record record = *recordPtr;
    cout << " " << message << ": " << record.getRecordKey() << " " << record.completeChecksumCheck();
    return recordPtr;
}