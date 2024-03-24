#include "TournamentPqTest.h"
#include "Testing/TestProviders/InOrderGenerator.h"
#include "Testing/TestProviders/ArrayProvider.h"
#include "TournamentPQ.h"
#include "Consumer.h"
#include "Witness.h"
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
using namespace std;


void TournamentPqTest::doTest(int numProviders) {
    int numItemsPerList = 10;

    InOrderGenerator i(numProviders * numItemsPerList, 16);
    Provider p = i;
    Witness before(p);


    list<vector<Record>> lists(numProviders);


    for(int i=0; i<numProviders ; i++) {
        vector<Record> l(numItemsPerList);
        lists.push_back(l);
    }

    for(int j=0 ; j<numItemsPerList ; j++) {
        for (auto it = lists.begin(); it != lists.end(); ++it){
            Record* ptr = before.next();
            Record r = *ptr;
            vector<Record> currentIndex = *it;
            currentIndex.push_back(r);
        }
    }

    vector<Provider> providers(numProviders);
    int index = 0;
    for (auto it = lists.begin(); it != lists.end(); ++it){
            string name ="Provider-"+index;
            vector<Record> currentIndex = *it;
            ArrayProvider p(name, currentIndex);
            providers[index] = p;
            index++;
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
