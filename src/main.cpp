
#include "OutlinedFiles/defs.h"

#include <unistd.h>

#include <iostream>

#include "OutlinedFiles/Iterator.h"
#include "OutlinedFiles/Scan.h"
#include "OutlinedFiles/Filter.h"
#include "OutlinedFiles/Sort.h"

#include <charconv>
#include <cstdint>
#include <cstring> // For std::strlen
#include <system_error>
#include <type_traits> // For std::is_integral

// generated by my good friend, ChatGpt
template<typename IntegerType, typename std::enable_if<std::is_integral<IntegerType>::value, bool>::type = true>
bool parseInteger(const char* str, IntegerType& outValue) {
    std::from_chars_result result = std::from_chars(str, str + std::strlen(str), outValue);

    if (result.ec == std::errc::invalid_argument) {
        std::cerr << "Error: Invalid argument." << std::endl;
        return false;
    } else if (result.ec == std::errc::result_out_of_range) {
        std::cerr << "Error: Result out of range." << std::endl;
        return false;
    } else if (result.ptr != str + std::strlen(str)) {
        // Not all characters were consumed, indicating some invalid input.
        std::cerr << "Error: Entire string not converted." << std::endl;
        return false;
    }

    // Success
    return true;
}

void usage(const char* message) {
    std::cout << "Error: " << message << std::endl;
    std::cout << "other usage stuff needs to go here" << std::endl;
    exit(1);
}

int main (int argc, char * argv []) {
    int opt;

    uint64_t numRecords = 1000;
    uint32_t recordSize = 128;
    uint32_t keyOffset = 8;
    uint32_t keyLength = 8;

    uint64_t cacheSize = 1L * 1024 * 1024;
    uint64_t memorySize = 100L * 1024 * 1024;
    uint64_t ssdSize = 10L * 1024 * 1024 * 1024;

    std::string traceFile = "";

    while ((opt = getopt(argc, argv, "o:c:s:k:l:x:y:z:")) != -1) {
        switch (opt) {
            case 'o':
                traceFile = optarg;
                break;
            case 'c':
                if(! parseInteger(optarg, numRecords)) {
                    usage("unable to parse record count");
                }
                break;
            case 's':
                if(! parseInteger(optarg, recordSize)) {
                    usage("unable to parse record size");
                }
                break;
            case 'k':
                if(! parseInteger(optarg, keyOffset)) {
                    usage("unable to parse key offset");
                }
                break;
            case 'l':
                if(! parseInteger(optarg, keyLength)) {
                    usage("unable to parse key offset");
                }
                break;
            case 'x':
                if(! parseInteger(optarg, cacheSize)) {
                    usage("unable to parse the cache size");
                }
                break;
            case 'y':
                if(! parseInteger(optarg, memorySize)) {
                    usage("unable to parse the memory size");
                }
                break;
            case 'Z':
                if(! parseInteger(optarg, ssdSize)) {
                    usage("unable to parse the ssd size");
                }
                break;
            case '?':
                if (optopt == 'f')
                    std::cerr << "Option -" << char(optopt) << " requires an argument.\n";
                else
                    std::cerr << "Unknown option: -" << char(optopt) << '\n';
                return 1;
            default: // Should not get here
                break;
        }
    }

    std::cout << "number of records: " << numRecords << std::endl;
    std::cout << "record size: " << recordSize << std::endl;
    std::cout << "key offset: " << keyOffset << std::endl;
    std::cout << "key length: " << keyLength << std::endl;

    std::cout << "cache size: " << cacheSize << std::endl;
    std::cout << "memory size: " << memorySize << std::endl;
    std::cout << "ssd size: " << ssdSize << std::endl;

    if(! traceFile.empty()) {
        std::cout << "trace file: " << traceFile << std::endl;
        TRACE (true);
    } else {
        std::cout << "No trace file specified." << std::endl;
        TRACE(false);
    }



    Plan * const plan = new ScanPlan (7);
    // new SortPlan ( new FilterPlan ( new ScanPlan (7) ) );

    Iterator * const it = plan->init ();
    it->run ();
    delete it;

    delete plan;

    return 0;
}
