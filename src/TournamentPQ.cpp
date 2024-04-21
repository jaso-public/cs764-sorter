#include "TournamentPQ.h"

/**
 * Compares two records
 *
 * @param first the first record for comparison
 * @param second the second record for comparison
 * @return true if the first record is smaller than the second record or the first record does not exist; else false
 */
bool isFirstWinner(shared_ptr<Record> &first, shared_ptr<Record> &second) {
    if(first == nullptr) {
        return false;
    } else if(second == nullptr) {
        return true;
    }
    return first->compareTo(second) < 0;
}

/**
 * Class constructor
 * @param providers a vector of providers to use to run a match
 * @param numProviders the total number of providers in the vector
 */
TournamentPQ::TournamentPQ(vector<shared_ptr<Provider>> providers, int numProviders): providers(providers) {
    this->numProviders = numProviders;
    this->losers = vector<int>(numProviders);

    for (int i=0 ; i<numProviders ; i++) {
       records.push_back(providers[i]->next());
    }

    vector<int> winners(numProviders);
    for(int match=numProviders-1; match>0 ; match--) {
        int h1 = match * 2;
        int h2 = h1 + 1;

        if(h1>=numProviders){
            h1 = h1-numProviders;
        } else {
            h1 = winners[h1];
        }
        if(h2>=numProviders){
            h2 = h2 - numProviders;
        } else {
            h2 = winners[h2];
        }

        if(isFirstWinner(records[h1], records[h2])) {
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
 * Gets the next record from the provider
 * @returns a pointer to the next record or a null pointer if a next record doesn't exist
 */
shared_ptr<Record> TournamentPQ::next() {
    int provider = losers[0];

    shared_ptr<Record> result = records[provider];
    if(!result) return nullptr;

    shared_ptr<Record> ptr = providers[provider]->next();
    records[provider] = ptr;
    int match = (provider + numProviders) / 2;

    int winner = provider;
    while(match > 0) {
        if(isFirstWinner(records[losers[match]], records[winner])) {
            int tmp = winner;
            winner = losers[match];
            losers[match] = tmp;
        }
        match = match / 2;
    }
    losers[0] = winner;

    return result;
}

