#include <unistd.h>  // for getopts

#include "Convert.h"
#include "Provider.h"
#include "IODevice.h"
#include "Consumer.h"
#include "Sorter.h"
#include "Witness.h"

using namespace std;

/**
 * This method displays an error message if something goes wrong within sortMain()
 * It also includes information about how to customize the sort
 * @param message the given error message
 */
void sortUsage(const char* message) {
    cout << "Error: " << message << endl;
    cout << " [options]" << endl;
    cout << "       -o<traceFileName>       name of the trace file to write to." << endl;
    cout << "       -i<inputFileName>       name of the input file to sort." << endl;
    cout << "       -j<outputFileName>      name of the output file to write the sorted records to. " << endl;
    cout << "       -g<ssdStagingFileName>  name of the SSD staging file to read/write to. " << endl;
    cout << "       -h<hddStagingFileName>  name of the HDD staging file to read/write to. " << endl;
    cout << "       -s<recordSize>          size of an individual record. " << endl;
    cout << "       -x<cacheSize>           desired size of the cache. " << endl;
    cout << "       -y<memorySize>          desired size of the memory (DRAM). " << endl;
    cout << "       -z<ssdSize>             desired size of the SSD. " << endl;
    cout << "       -d                      remove duplicate records. " << endl;
    cout << "       -v                      verbose output. " << endl;
    cout << endl;
    exit(1);
}

/**
 * This function executes the external merge sort logic on an input file
 * @param argc standard main number od args
 * @param argv char** args for the program
 */
int sortMain (int argc, char * argv []) {

    if(argc==1) {
        sortUsage("usage");
    }

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

    bool verbose = false;
    bool deduplicate = false;

    optind = 1;
    while ((opt = getopt(argc, argv, "o:i:j:g:h:s:k:l:x:y:z:vd")) != -1) {
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
            case 'g':
                ssdStagingFileName = optarg;
                break;
            case 'h':
                hddStagingFileName = optarg;
                break;
            case 's':
                if(! parseInteger(optarg, recordSize)) {
                    sortUsage("unable to parse record size");
                }
                break;
            case 'x':
                if(! parseInteger(optarg, cacheSize)) {
                    sortUsage("unable to parse the cache size");
                }
                break;
            case 'y':
                if(! parseInteger(optarg, memorySize)) {
                    sortUsage("unable to parse the memory size");
                }
                break;
            case 'z':
                if(! parseInteger(optarg, ssdSize)) {
                    sortUsage("unable to parse the ssd size");
                }
                break;
            case 'd':
                deduplicate = true;
                break;
            case 'v':
                verbose = true;
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
    *out << "    record size      : " << recordSize << std::endl;
    *out << "    deduplicate      : " << (deduplicate ? "true" : "false") << std::endl;
    Record::staticInitialize(recordSize);

    std::ostream* verboseOut = nullptr;
    if(verbose) verboseOut = out;

    auto cfg = make_unique<SorterConfig>();
    auto ssdDevice = make_shared<IODevice>(ssdStagingFileName, verboseOut);
    auto hddDevice = make_shared<IODevice>(hddStagingFileName, verboseOut);

    cfg->ssdDevice = ssdDevice;
    cfg->hddDevice = hddDevice;
    cfg->memoryBlockSize = cacheSize;
    cfg->memoryBlockCount = memorySize / cacheSize;
    cfg->ssdStorageSize = ssdSize;
    cfg->ssdReadSize = ssdReadSize;

    cfg->writeStats(*out);

    auto inputDevice = make_shared<IODevice>(inputFileName, verboseOut);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    auto lower = make_shared<Witness>(provider);
    auto sorter = make_shared<Sorter>(cfg, lower, verboseOut);
    shared_ptr<Provider> nextProvider = sorter;
    if(deduplicate) nextProvider = make_shared<DeduplicaterProvider>(sorter);
    auto upper = make_shared<Witness>(nextProvider);
    auto outputDevice = make_shared<IODevice>(outputFileName, verboseOut);
    auto consumer = make_shared<DeviceConsumer>(upper, outputDevice, hddReadSize);

    consumer->consume();

    sorter->writeStats(*out);
    lower->writeStats(*out, "pre-sort");
    upper->writeStats(*out, "post-sort");
    if (deduplicate){
        auto deduplicaterProvider = std::dynamic_pointer_cast<DeduplicaterProvider>(nextProvider);
        deduplicaterProvider->writeDuplicateStats(*out);
    }
    inputDevice->writeStats(*out);
    outputDevice->writeStats(*out);
    ssdDevice->writeStats(*out);
    hddDevice->writeStats(*out);

    return 0;
}
