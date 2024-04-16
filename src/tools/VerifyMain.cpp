#include <unistd.h>  // for getopts

#include "Convert.h"
#include "Provider.h"
#include "IODevice.h"
#include "Consumer.h"
#include "Witness.h"

using namespace std;

void verifyUsage(const char* message) {
    std::cout << "Error: " << message << std::endl;
    std::cout << "other usage stuff needs to go here" << std::endl;
    exit(1);
}

int verifyMain (int argc, char * argv []) {
    int opt;

    string inputFileName = "input.txt";
    uint32_t recordSize = 128;
    uint32_t hddReadSize = 256 * 1024;

    while ((opt = getopt(argc, argv, "i:s:")) != -1) {
        switch (opt) {
            case 'i':
                inputFileName = optarg;
                break;
             case 's':
                if(! parseInteger(optarg, recordSize)) {
                    verifyUsage("unable to parse record size");
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

    *out << "record size: " << recordSize << std::endl;
    Record::staticInitialize(recordSize);


    auto inputDevice = make_shared<IODevice>(inputFileName);
    auto provider = make_shared<DeviceProvider>(inputDevice, hddReadSize);
    auto witness = make_shared<Witness>(provider);
    auto consumer = make_shared<NoopConsumer>(witness);

    consumer->consume();

    inputDevice->writeStats(*out);
    witness->writeStats(*out, "VerifyTool");
    *out << "record size: " << recordSize << std::endl;
    return 0;
}
