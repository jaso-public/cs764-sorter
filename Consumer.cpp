#include "Consumer.h"
#include "Providers/Provider.h"
#include "Records/Record.h"
using namespace std;
#include <iostream>

/**
 * Initializes consumer constructor
 * @param givenSource the source to get records from
 */
Consumer::Consumer(Provider givenSource) {
    this->source = givenSource;
}

/**
 * Continues to get records until a null record pointer has been reached
 */
void Consumer::consume() {
    while (true){
        Record* ptr = source.next();
        // if null ptr then end consuming
        if (!ptr){
            return;
        }
    }
}

// main method to show it consumes 10 records then stops
/**
int main(){
    //create a provider to generate 10 records
    Provider p(10,10,8);
    Consumer c(p);
    c.consume();
}
 */

int main(){};