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

/**
 * TournamentPQ constructor
 * Determines which records are winners and losers in the given tournament
 * @param givenProviders an array of providers that can generate records
 * @param keyOffset the key offset value of the record
 */
Record TournamentPQ::next() {
    int provider = losers[0];

    Record result = records[provider];
    if (!result) return nullptr;

    records[provider] = providers[provider].next();
    int match = (provider + size) /2;

    int winner = provider;
    while (match>0){
        if (firstWin(losers[match], winner)){
            int temp = winner;
            winner = losers[match];
            losers[match] = temp
        }
        match = match/2;
    }
    losers[0] = winner;
}

/**
 * Runs a match between to provider.
 *
 * @param first the first provider in the match.
 * @param second the second provider in the match.
 * @return true if the first provider wins the match, false otherwise.
 */
bool TournamentPQ::firstWin(int first, int second) {
    Record* r1Ptr = records[first];
    Record* r2Ptr = records[second];
    Record r1 = *r1Ptr;
    Record r2 = *r2Ptr;
    if (!r1Ptr) return false;
    else if (!r2Ptr) return true;
    else if (r1 > r2) return true;
    else return false;
}