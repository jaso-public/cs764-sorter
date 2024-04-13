#include <unistd.h>  // for getopts
#include <iostream>

#include "Convert.h"
#include "Provider.h"
#include "IODevice.h"
#include "Consumer.h"

using namespace std;

void usage(const char* programName, const char* message) {
    cout << "Error: " << message << endl;
    cout << "usage: " << programName << " [options]" << endl;
    cout << "       -f<filename>    name of the output file to generate." << endl;
    cout << "       -c<recordCount> number of records to generate." << endl;
    cout << "       -s<recordSize>  size of the records to generate. " << endl;
    cout << "       -p<probabilty>  probability of generating an alternate key " << endl;
    cout << "       -r<range>       possible range of values for the alternate key. " << endl;
    cout << "       -n              make the last byte of the record a new line." << endl;
    cout << endl;
    cout << "This generator creates records from the character set A-Z, a-z, 0-9.  Normally," << endl;
    cout << "it just generates random strings using this character set.  You can also" << endl;
    cout << "request that a newline character is added to the end of the record, this is handy" << endl;
    cout << "if you want to examine the records in vi or use unix command line tools to analyze the file." << endl;
    cout << endl;
    cout << "Although the generator makes random keys, the likelihood of getting duplicate keys" << endl;
    cout << "is very low (depending on your key length).  For some test loads, you may want the " << endl;
    cout << "generated file to contain duplicate keys with a much higher probability.  To do this" << endl;
    cout << "you can specify the probability (-p) and range (-r) for the generator.  The probablity" << endl;
    cout << "is the liklihood that the next key generated will be created in the range specified.  " << endl;
    cout << "For example if you specify a probability of 0.1 and a range of 100 (-p 0.1 -r 100) then" << endl;
    cout << "1/10 of the records generated on average will have keys in the range [0,100].  If you" << endl;
    cout << "were to genereate one million records, then about 100,000 of them would have keys in the" << endl;
    cout << "range.  Therefore you should expect on average that there 1000 duplicate keys for each of" << endl;
    cout << "the specially generated keys." << endl;
    cout << endl;

    exit(1);
}

int main (int argc, char * argv []) {

    string fileName = "input.txt";
    uint64_t recordCount = 1000;
    uint32_t recordSize = 128;
    double_t probability = 0;
    uint64_t range = 100;
    bool newLine = false;

    int opt;
    while ((opt = getopt(argc, argv, "f:c:s:p:r:nh")) != -1) {
        switch (opt) {
            case 'h':
                usage(argv[0], "This help message.");
                break;
            case 'f':
                fileName = optarg;
                break;
            case 'n':
                newLine = true;
                break;
            case 'c':
                if(! parseInteger(optarg, recordCount)) {
                    usage(argv[0], "unable to parse record count");
                }
                break;
            case 's':
                if(! parseInteger(optarg, recordSize)) {
                    usage(argv[0], "unable to parse record size");
                }
                break;
            case 'p':
                if(! parseFloatingPoint(optarg, probability)) {
                    usage(argv[0], "unable to parse probability for duplicates");
                }
                break;
            case 'r':
                if(! parseInteger(optarg, range)) {
                    usage(argv[0], "unable to parse range of the duplicate keys");
                }
                break;
            case '?':
                if (optopt == 'f')
                    cerr << "Option -" << char(optopt) << " requires an argument.\n";
                else
                    cerr << "Unknown option: -" << char(optopt) << '\n';
                return 1;
            default: // Should not get here
                break;
        }
    }

    std::ostream* out = &std::cout;  // Default to cout

    *out << "outputFile: " << fileName << endl;
    *out << "record count: " << recordCount << endl;
    *out << "record size: " << recordSize << endl;
    *out << "probability: " << probability << endl;
    *out << "range: " << range << endl;
    *out << "new line: " << newLine << endl;

    Record::staticInitialize(recordSize);

    auto provider = make_shared<RandomProvider>(recordCount, probability, range, newLine);
    auto device = make_shared<IODevice>(fileName);
    auto consumer = make_shared<DeviceConsumer>(provider, device, 256*1024);
    consumer->consume();

    device->writeStats(*out);
    return 0;
}
