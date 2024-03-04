#include "TournamentPQ.h"
#include "Provider.h"
#include "Record.h"
#include<iostream>
#include<array>

/**
   * Initializes TournamentPQ constructor
   * Determines which records are winners and losers in the given tournament
   * @param givenProviders an array of providers that can generate records
   */
TournamentPQ::TournamentPQ(Provider *givenProviders, uint32_t givenKeyOffset) {
    // sets given providers to class providers variable
    providers = *givenProviders;
    // sets givenKeyOffset to class offset variable
    keyOffset = givenKeyOffset;

    // calculates the total number of given providers
    size = sizeof(providers)/sizeof(providers[0]);

    // creates fills the records array with the next value from every provider
    this->records = new Record(size, keyOffset);
    for (int i = 0; i< size; i++){
        records[i] = providers[i].next();
    }

    // creates losers array to be the size of the number of next records obtained/number of providers
    loser = malloc(sizeof(size));
    // creates a winners array of keys
    uint64_t* winnersArray = malloc(sizeof(size));
    uint64_t *winners = (uint64_t*) winnersArray;

    //TODO: begin conceptual explanation here
    for (int match=size-1; match > 0; match--){
        int h1 = match * 2;
        int h2 = h1 + 1;
        if (h1>=size) h1 = h1-size; else h1 = winners[h1];
        if (h2>=size) h2 = h2-size; else h2 = winners[h2];

        if (firstWin(h1,h2)){
            winners[match] = h1;
            loser[match] = h2;
        } else {
            winners[match] = h2;
            losers[match] = h1;
        }

        // loser[0] is really the winner of the overall tournament
        losers[0] = winners[1];
    }
}

//TODO: ending on next record method
// need to make it return a pointer instead of a record