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
    Record::staticInitialize(120);
    shared_ptr<Provider> source = make_shared<RandomProvider>(numProviders);
    shared_ptr<Witness> before = make_shared<Witness>(source);

    vector<shared_ptr<Provider>> singles(numProviders);
    for (int i = 0; i < numProviders; ++i) {
        singles[i] = make_unique<SingleProvider>();
        shared_ptr<Record> recordPtr = source->next();
        shared_ptr<SingleProvider> singleProvider = dynamic_pointer_cast<SingleProvider>(singles[i]);
        singleProvider->reset(recordPtr);
    }

    shared_ptr<TournamentPQ> pq = make_shared<TournamentPQ>(singles, numProviders);
    shared_ptr<Witness> w = make_shared<Witness>(pq);
    shared_ptr<NoopConsumer> consumer = make_shared<NoopConsumer>(w);
    consumer->consume();


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

