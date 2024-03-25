#ifndef CS764_SORTER_TOURNAMENTPQ_H
#define CS764_SORTER_TOURNAMENTPQ_H
#include "Providers/SingleProvider.h"
#include <iostream>
#include <vector>
using namespace std;


/**
 * This is the tournament tree priority queue that will be utilized for sorting record keys
 */
template<typename T>
class TournamentPQ: public Provider {
private:
    vector<T> providers;
    vector<Record> records;
    vector<int> losers;
    int numProviders;
    // key offset of record
    uint32_t keyOffset;

    /**
    * Runs a match between two provider
    *
    * @param first the first provider in the match
    * @param second the second provider in the match
    * @return true if the first provider wins the match, false otherwise.
    */
    bool isFirstWinner(int first, int second);

public:
    TournamentPQ(vector<T>& providers, uint32_t givenKeyOffset, int numProviders);
    Record* next() override;
};


#endif //CS764_SORTER_TOURNAMENTPQ_H
