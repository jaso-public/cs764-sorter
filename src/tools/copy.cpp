#include <unistd.h>  // for getopts
// #include <iostream>

#include "Convert.h"
#include "Provider.h"
#include "IODevice.h"
#include "Consumer.h"
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
    string outputFileName = "output.txt";
    uint32_t recordSize = 128;

    uint32_t ssdReadSize = 16 * 1024;
    uint32_t hddReadSize = 256 * 1024;



    while ((opt = getopt(argc, argv, "o:i:j:d:h:c:s:k:l:x:y:z:")) != -1) {
        switch (opt) {
            case 'i':
                inputFileName = optarg;
                break;
            case 'j':
                outputFileName = optarg;
                break;
             case 's':
                if(! parseInteger(optarg, recordSize)) {
                    usage("unable to parse record size");
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
    *out << "input file: " << inputFileName << std::endl;
    *out << "output file: " << outputFileName << std::endl;
    *out << "record size: " << recordSize << std::endl;
    Record::staticInitialize(recordSize);


    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    auto witness = make_shared<Witness>(provider);
    auto outputDevice = make_shared<IODevice>(outputFileName);
    auto consumer = make_shared<DeviceConsumer>(witness, outputDevice, hddReadSize);

    consumer->consume();

    inputDevice->writeStats(*out);
    outputDevice->writeStats(*out);
    witness->writeStats(*out, "copyTool");

    return 0;
}
