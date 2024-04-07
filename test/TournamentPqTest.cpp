#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <cassert>

#include "Record.h"
#include "Provider.h"
#include "Witness.h"
#include "TournamentPQ.h"
#include "Consumer.h"

#include "test/helpers/Generators.h"
#include "test/helpers/ArrayProvider.h"

using namespace std;


void doTest(int numProviders) {
    int itemsPerProvider = 10;
    cerr << "first test " << numProviders <<" " << itemsPerProvider << endl;

    // make a big list of records
    auto records = generateInOrder(numProviders * itemsPerProvider);

    cerr << "generateInOrder\n";

    // make an array provider so we can pass the records thru a witness

    ArrayProvider ap("source", records);
    Witness before(&ap);

    cerr << "made  Witness before\n";

    vector<shared_ptr<Provider>> providers;

    for(int i=0; i<numProviders ; i++) {
        vector<shared_ptr<Record>> perProviderRecords;
        for (int j = 0; j < 10; j++) {
            perProviderRecords.push_back(before.next());
        }
        providers.push_back(make_unique<ArrayProvider>("prov", perProviderRecords));
    }


    TournamentPQ pq(providers, numProviders);
    Witness w(&pq);
    Consumer c(&w);
    c.consume();

    assert(w.isSorted);
    assert(("The count of the before witness did have the same checksum as the w witness but should have" && before.getCrc() == w.getCrc()));
    assert(("The count of the before witness did have the same checksum as the w witness but should have" && before.getCrc() == w.getCrc()));
}

void testVariousNumberOfProviders() {
    for(int i=1; i<100; i++) {
        doTest(i);
    }
}


int main(){
    TournamentPqTest test;
    test.testVariousNumberOfProviders();
}

