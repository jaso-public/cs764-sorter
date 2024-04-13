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
    string ssdStagingFileName = "ssd.staging";
    string hddStagingFileName = "hdd.staging";

    uint32_t recordSize = 128;

    uint64_t cacheSize = 1L * 1024 * 1024;
    uint64_t memorySize = 100L * 1024 * 1024;
    uint64_t ssdSize = 10L * 1024 * 1024 * 1024;

    uint32_t ssdReadSize = 16 * 1024;
    uint32_t hddReadSize = 256 * 1024;



    while ((opt = getopt(argc, argv, "o:i:j:d:h:s:k:l:x:y:z:")) != -1) {
        switch (opt) {
            case 'o':
                traceFileName = optarg;
                break;
            case 'i':
                inputFileName = optarg;
                break;
            case 'j':
                outputFileName = optarg;
                break;
            case 'd':
                ssdStagingFileName = optarg;
                break;
            case 'h':
                hddStagingFileName = optarg;
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

    std::ostream* out = &std::cout;  // Default to cout
    std::ofstream file;

    if(traceFileName.length() > 0) {
        file.open(traceFileName);
        if (!file.is_open()) {
            std::cerr << "Failed to open the file: " << traceFileName << std::endl;
            return 1;  // Exit if file cannot be opened
        }
        out = &file;  // Redirect output to file
    }

    *out << "Parameters:" << traceFileName << std::endl;
    *out << "    trace file       : " << traceFileName << std::endl;
    *out << "    input file       : " << inputFileName << std::endl;
    *out << "    output file      : " << outputFileName << std::endl;
    *out << "    ssd staging file : " << ssdStagingFileName << std::endl;
    *out << "    hdd staging file : " << hddStagingFileName << std::endl;

    *out << "    record size: " << recordSize << std::endl;
    Record::staticInitialize(recordSize);

    auto cfg = make_unique<SorterConfig>();
    auto ssdDevice = make_shared<IODevice>(ssdStagingFileName);
    auto hddDevice = make_shared<IODevice>(hddStagingFileName);

    cfg->ssdDevice = ssdDevice;
    cfg->hddDevice = hddDevice;
    cfg->memoryBlockSize = cacheSize;
    cfg->memoryBlockCount = memorySize / cacheSize;
    cfg->ssdStorageSize = ssdSize;

    cfg->writeStats(*out);

    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    auto lower = make_shared<Witness>(provider);
    auto sorter = make_shared<Sorter>(cfg, lower);
    auto upper = make_shared<Witness>(sorter);
    auto outputDevice = make_shared<IODevice>(outputFileName);
    auto consumer = make_shared<DeviceConsumer>(upper, outputDevice, hddReadSize);

    consumer->consume();

    sorter->writeStats(*out);
    lower->writeStats(*out, "pre-sort");
    upper->writeStats(*out, "post-sort");
    inputDevice->writeStats(*out);
    outputDevice->writeStats(*out);
    ssdDevice->writeStats(*out);
    hddDevice->writeStats(*out);

    return 0;
}
