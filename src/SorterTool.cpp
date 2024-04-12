#include <unistd.h>  // for getopts
// #include <iostream>

#include "Convert.h"
#include "Provider.h"
#include "IODevice.h"
#include "Consumer.h"
#include "Sorter.h"
#include "Witness.h"

using namespace std;

void usage(const char* message) {
    std::cout << "Error: " << message << std::endl;
    std::cout << "other usage stuff needs to go here" << std::endl;
    exit(1);
}

int main (int argc, char * argv []) {
    int opt;

    string inputFileName = "input.txt";
    string traceFileName = "";
    string outputFileName = "output.txt";
    string ssdStagingFileName = "ssd.stating";
    string hddStagingFileName = "hdd.staging";

    uint64_t numRecords = 1000;
    uint32_t recordSize = 128;

    uint64_t cacheSize = 1L * 1024 * 1024;
    uint64_t memorySize = 100L * 1024 * 1024;
    uint64_t ssdSize = 10L * 1024 * 1024 * 1024;

    uint32_t ssdReadSize = 16 * 1024;
    uint32_t hddReadSize = 256 * 1024;



    while ((opt = getopt(argc, argv, "o:c:s:k:l:x:y:z:")) != -1) {
        switch (opt) {
            case 'o':
                traceFileName = optarg;
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
            case 'z':
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

    std::cout << "cache size: " << cacheSize << std::endl;
    std::cout << "memory size: " << memorySize << std::endl;
    std::cout << "ssd size: " << ssdSize << std::endl;

    auto cfg = make_unique<SorterConfig>();

    auto ssdDevice = make_shared<IODevice>(ssdStagingFileName);
    auto hddDevice = make_shared<IODevice>(hddStagingFileName);

    cfg->ssdDevice = ssdDevice;
    cfg->hddDevice = hddDevice;

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    auto lower = make_shared<Witness>(provider);
    auto sorter = make_shared<Sorter>(cfg, lower);
    auto upper = make_shared<Witness>(sorter);
    auto outputDevice = make_shared<IODevice>(outputFileName);
    auto consumer = make_shared<DeviceConsumer>(upper, outputDevice, hddReadSize);

    consumer->consume();

    inputDevice->writeStats();
    outputDevice->writeStats();
    ssdDevice->writeStats();
    hddDevice->writeStats();

    return 0;
}
