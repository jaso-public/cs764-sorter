#ifndef CS764_SORTER_TOURNAMENTPQ_H
#define CS764_SORTER_TOURNAMENTPQ_H
#include "Providers/Provider.h"


/**
 * This is the tournament tree priority queue that will be utilized for sorting record keys
 */
class TournamentPQ:Provider {
private:
    // a pointer to an array of providers to generate records
    Provider *providersPtr;
    // a pointer to an array of created records
    Record *records;
    // array of loser records uncovered during the tournament
    uint64_t* losers;
    // the number of record providers
    uint64_t size;
    // key offset of record
    uint32_t keyOffset;
    /**
    * Runs a match between two provider
    *
    * @param first the first provider in the match
    * @param second the second provider in the match
    * @return true if the first provider wins the match, false otherwise.
    */
    bool firstWin(int first, int second);

public:
    /**
     * TournamentPQ constructor
     * Determines which records are winners and losers in the given tournament
     * @param givenProviders a pointer to an array of providers
     * @param keyOffset the key offset value of the record
     */
    TournamentPQ(Provider *givenProviders, uint32_t givenKeyOffset);
    /**
     * Returns the next winning record of the tournament
     * @return the next winning record
     */
    Record next();

};


#endif //CS764_SORTER_TOURNAMENTPQ_H
