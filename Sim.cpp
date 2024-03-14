#include <iostream>
using namespace std;

/**
 * This class simulates filling the SSD and HDD with bytes of sorted data
 * @return prints out the streams, number of bytes to use, and size for both SSD and HDD
 */
int main(){
    // aids in calculating number of bytes to move into memory
    float percentage = 0.01F;
    // total number of keys to sort
    int numToSort = 120 * 1024;
    // keys sorted
    int sorted = 0;
    // free RAM blocks
    int freeBlocks = 99;
    // SSD free space
    int ssdFree = 10 * 1024;
    // total SSD streams and size
    int ssdStreams = 0;
    int ssdSize = 0;
    // total HDD streams and size
    int hddStreams = 0;
    int hddSize = 0;

    // continues until all records are sorted
    while (sorted < numToSort){
        // keeps track of keys sorted
        sorted += freeBlocks;
        freeBlocks = 0;
        // computes number of sorted keys to move to lower memory
        int numToMove = (int)(sorted * percentage);
        if(numToMove < 1) numToMove = 1;
        if(numToMove > 99) numToMove = 99;
        // checks that there is SSD space to move bytes
        if(ssdFree > 0) {
            // uses all available SSD space
            if(numToMove > ssdFree) numToMove = ssdFree;
            ssdFree -= numToMove;
            ssdStreams++;
            cout << "ssd: " << ssdStreams << " " << numToMove << " " << ssdSize << "\n";
        } else {
            // utilizes HDD space if SSD is full
            hddSize += numToMove;
            hddStreams++;
            cout << "hdd: " << hddStreams << " " << numToMove << " " << hddSize << "\n";
        }
        // keeps of all keys that were placed into memory
        freeBlocks += numToMove;
    }
    // output computation summary
    cout << "ssdStreams: " << ssdStreams << "\n";
    cout << "hddStreams: " << hddStreams << "\n";
    cout << "hddSize: " << hddSize << "\n";

    // outputs total number of streams used
    double total = ssdStreams + hddStreams;
    total /= 16;
    cout << "total: " << total << "\n";
}
