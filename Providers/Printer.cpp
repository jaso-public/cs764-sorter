#include "Printer.h"
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;
/**
   * Class constructor of the printer that sets the given variables to the class variables
   * @param givenSource given provider to get records from
   * @param givenMessage message to print out with each record
   */
Printer::Printer(Provider givenSource, string givenMessage) {
    this->source = givenSource;
    this->message = givenMessage;
}

/*
 * Obtains the next record from the provider with a message
 * If the record is null, it will print out the time elapsed (milliseconds), message, and a null response to console
 * If the record is not null, it will print out the time elapsed (milliseconds), message, record's key, and checksum to console
 * @returns a pointer to the record or a null pointer
 */
Record* Printer::next() {
    Record* recordPtr = source.next();
    // if record pointer is null
    if (!recordPtr){
        cout << " " << message << ": record is null!"<< "\n";
        return recordPtr;
    }
    Record record = *recordPtr;
    cout << " " << message << ": " << "Key: " << record.getRecordKey() << " Checksum: " << record.completeChecksumCheck() << "\n";
    return recordPtr;
}

int main(){
    // create a printer to generate 10 records
    Provider provider(10,10,8);
    Printer printer(provider, "this is a test message");
    // checks that all 10 records are generated then null pointer is reached
    for (int i = 0; i < 11; i++) {
        Record *ptr = printer.next();
    }
}