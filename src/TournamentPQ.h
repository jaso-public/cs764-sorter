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
     * Gets the next record from the provider
     * @returns a pointer to the next record or a null pointer if a next record doesn't exist
     */
    shared_ptr<Record> next() override;

private:
    vector<shared_ptr<Provider>> providers;   // vector of provider pointers to return records for matches
    vector<shared_ptr<Record>> records;       // vector of records to compare for sorting
    vector<int> losers;                       // vector of losers from the tournament
    int numProviders;                         // total number of providers given to the class
};
