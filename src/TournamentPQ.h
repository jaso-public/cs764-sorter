#pragma once

#include <iostream>
#include <vector>

#include "Record.h"
#include "Provider.h"

using namespace std;


/**
 * This is the tournament tree priority queue class that is utilized for sorting record keys
 */
class TournamentPQ: public Provider {
public:
    /**
     * Class constructor
     * @param providers a vector of providers to use to run a match
     * @param numProviders the total number of providers in the vector
     */
    TournamentPQ(vector<shared_ptr<Provider>> providers, int numProviders);
    /**
     * Returns the next unique record in the sorted sequence
     */
    shared_ptr<Record> next() override;

private:
    //vector of provider pointers to return records for matches
    vector<shared_ptr<Provider>> providers;
    //vector of records to compare for sorting
    vector<shared_ptr<Record>> records;
    //vector of losers from the tournament
    vector<int> losers;
    //total number of providers given to the class
    int numProviders;
};
