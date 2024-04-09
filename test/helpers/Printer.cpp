#include "Printer.h"

/*
 * Obtains the next record from the provider with a message
 * If the record is null, it will print out the time elapsed (milliseconds), message, and a null response to console
 * If the record is not null, it will print out the time elapsed (milliseconds), message, record's key, and checksum to console
 * @returns a pointer to the record or a null pointer
 * Sources for time:
 * https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
 * https://codereview.stackexchange.com/questions/11921/getting-current-time-with-milliseconds
 */
shared_ptr<Record> Printer::next() {
    // obtains the current time to the millisecond to print out
    time_t now = time(0);
    tm *localTime = localtime(&now);
    timeval currentTime;
    gettimeofday(&currentTime, NULL);
    int milliSeconds = currentTime.tv_usec / 1000;
    cout << "Current Time: "<< localTime->tm_hour << ":";
    cout << localTime->tm_min << ":";
    cout << localTime->tm_sec << ":";
    cout << milliSeconds;
    shared_ptr<Record> recordPtr = source->next();
    // if record pointer is null
    if (!recordPtr){
        cout << " " << message << ": record is null!"<< "\n";
    } else {
        cout << " " << message << " Checksum: " << recordPtr->checksum() << "\n";
    }
    return recordPtr;
}

