#include "TournamentPqTest.h"
#include "Testing/TestProviders/InOrderGenerator.h"
#include "../TournamentPQ.h"
#include "../Consumer.h"
#include "Witness.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;


void TournamentPqTest::doTest(int numProviders) {
    int numItemsPerList = 10;

    InOrderGenerator i(numProviders * numItemsPerList, 16);
    Provider p = i;
    Witness before(p);


    vector<vector<Record>> lists(numProviders);

    for(int i=0; i<numProviders ; i++) {
        vector<Record> l(numItemsPerList);
        lists[i] = l;
    }

    for(int j=0 ; j<numItemsPerList ; j++) {
        for(int i=numProviders-1 ; i>=0 ; i--) {
            Record* ptr = before.next();
            Record r = *ptr;
            lists[i].push_back(r);
        }
    }

    vector<Provider> providers(numProviders);
    for(int i=0; i<numProviders ; i++) {
        //TODO: fix iterator
        ArrayProvider p("Provider-"+i, lists[i].iterator())
        providers[i] = p;
    }


    TournamentPQ pq(providers, 8, providers.size());
    Witness w(pq);
    Consumer c(w);
    c.consume();

    assert(w.isSorted);
    assert(("The count of the before witness did have the same checksum as the w witness but should have", before.getCrc() == w.getCrc()));
}

void TournamentPqTest::testVariousNumberOfProviders() {
    for(int i=1; i<100; i++) {
        doTest(i);
    }
}
