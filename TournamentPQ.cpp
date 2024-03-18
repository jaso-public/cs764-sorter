#include "TournamentPQ.h"
#include "Providers/Provider.h"
#include "Records/Record.h"
#include<iostream>
#include<array>

/**
   * Initializes TournamentPQ constructor
   */


TournamentPQ::TournamentPQ(vector<Provider> providers, uint32_t givenKeyOffset, int numProviders) {
    this->providers = providers;
    this->numProviders = numProviders;
    this->keyOffset = keyOffset;


    // create and fill the records array
    vector<Record> r(numProviders);
    this->records = r;
    for(int i=0 ; i<numProviders ; i++) {
        Record* ptr = providers[i].next();
        records[i] = *ptr;
    }

    vector<int> losers(numProviders);
    vector<int> winners(numProviders);
    for(int match=numProviders-1 ; match>0 ; match--) {
        int h1 = match * 2;
        int h2 = h1 + 1;
        if(h1>=numProviders) h1 = h1-numProviders; else h1 = winners[h1];
        if(h2>=numProviders) h2 = h2-numProviders; else h2 = winners[h2];

        if(isFirstWinner(h1, h2)) {
            winners[match] = h1;
            losers[match] = h2;
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
 */
Record* TournamentPQ::next() {
    int provider = losers[0];

    Record result = records[provider];
    if(result.record == nullptr) return nullptr;

    //TODO: here
    records[provider] = providers[provider].next();
    int match = (provider + numProviders) / 2;

    int winner = provider;
    while(match > 0) {
        if(isFirstWinner(losers[match], winner)) {
            int tmp = winner;
            winner = losers[match];
            losers[match] = tmp;
        }
        match = match / 2;
    }
    losers[0] = winner;

    return result;
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