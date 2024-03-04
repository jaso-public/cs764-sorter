#ifndef CS764_SORTER_TOURNAMENTPQ_H
#define CS764_SORTER_TOURNAMENTPQ_H
#include "Provider.h"


/**
 * This is the tournament priority queue that will be utilized for sorting
 */
class TournamentPQ:Provider {
private:
    // an array of providers to generate records
    Provider* providers final;
    // array of created records
    Record* records final;
    // array of loser keys
    uint64_t* losers final;
    // the number of record providers
    uint64_t size final;
    // key offset of record
    uint32_t keyOffset;
    /**
    * Runs a match between to provider
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
     * @param givenProviders an array of providers that can generate records
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
