#include "Consumer.h"
#include "Provider.h"
#include "Record.h"
using namespace std;
#include <iostream>

/**
 * Initializes consumer constructor
 * @param givenSource the source to get records from
 */
Consumer::Consumer(Provider givenSource) {
    source = givenSource;
}

/**
 * Continues to get records until a null record pointer has been reached
 */
void Consumer::consume() {
    bool moreRecords = true;
    while (moreRecords){
        Record* ptr = source.next();
        // if null ptr then end consuming
        if (!ptr){
            moreRecords = false;
            //cout << "Null pointer was reached";
        }
        //TODO: in for testing, can delete else statement later
        else {
            Record r = *ptr;
            cout << r.record << "\n";
        }
    }
}

// main method so show it consumes 10 records then stops
/**
int main(){
    //create a provider to generate 10 records
    Provider p(10,10,8);
    Consumer c(p);
    c.consume();
}
 */