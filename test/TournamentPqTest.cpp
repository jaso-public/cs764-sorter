#include <iostream>
#include <vector>
#include <cassert>

#include "Record.h"
#include "Provider.h"
#include "Witness.h"
#include "TournamentPQ.h"
#include "src/Generator.h"
#include "src/Consumer.h"

using namespace std;


void doTest(int numProviders) {
    int itemsPerProvider = 10;
    cerr << "first test " << numProviders <<" " << itemsPerProvider << endl;

    // make a big list of records
    auto records = generateInOrder(numProviders * itemsPerProvider);

    cerr << "generateInOrder\n";

    // make an array provider so we can pass the records thru a witness

    shared_ptr<ArrayProvider> providerPtr = make_shared<ArrayProvider>("name", records);
    shared_ptr<Witness> before = make_shared<Witness>(providerPtr);

    cerr << "made  Witness before\n";

    vector<shared_ptr<Provider>> providers;

    for(int i=0; i<numProviders ; i++) {
        vector<shared_ptr<Record>> perProviderRecords;
        for (int j = 0; j < 10; j++) {
            perProviderRecords.push_back(before->next());
        }
        providers.push_back(make_unique<ArrayProvider>("prov", perProviderRecords));
    }

    shared_ptr<TournamentPQ> pq = make_shared<TournamentPQ>(providers, numProviders);
    shared_ptr<Witness> w = make_shared<Witness>(pq);
    Consumer consumer(w);
    consumer.consume();

    assert(w->isSorted());
    assert(("The count of the before witness did have the same checksum as the w witness but should have" && before->getChecksum() == w->getChecksum()));
    assert(("The count of the before witness did have the same checksum as the w witness but should have" && before->getChecksum() == w->getChecksum()));
}

void testVariousNumberOfProviders() {
    for(int i=1; i<100; i++) {
        doTest(i);
    }
}


int main(){
    testVariousNumberOfProviders();
}

