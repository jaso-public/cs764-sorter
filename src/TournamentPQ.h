#ifndef CS764_SORTER_TOURNAMENTPQ_H
#define CS764_SORTER_TOURNAMENTPQ_H

#include <iostream>
#include <vector>

#include "Record.h"
#include "Provider.h"

using namespace std;


/**
 * This is the tournament tree priority queue that will be utilized for sorting record keys
 */
class TournamentPQ: public Provider {
public:
    TournamentPQ(vector<shared_ptr<Provider>> providers, int numProviders);
    shared_ptr<Record> next() override;
    bool isFirstWinner(int first, int second);

private:
    vector<shared_ptr<Provider>> providers;
    vector<shared_ptr<Record>> records;
    vector<int> losers;
    int numProviders;
};

#endif //CS764_SORTER_TOURNAMENTPQ_H
