package sorter;

public class TournamentPQ implements Provider {

    private final Provider[] providers;
    private final Record[] records;
    private final int[] losers;
    private final int numProviders;
    
    
    public TournamentPQ(Provider[] prov, int numProviders) {
        providers = prov;
        this.numProviders = numProviders;
         
        // create and fill the records array
        this.records = new Record[numProviders];
        for(int i=0 ; i<numProviders ; i++) {
            records[i] = providers[i].next();
        }
        
        losers = new int[numProviders];
        int[] winners = new int[numProviders];
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
    

    @Override
    public Record next() {
        int provider = losers[0];
        
        Record result = records[provider];
        if(result == null) return null;
        
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
    private boolean isFirstWinner(int first, int second) {
        Record r1 = records[first];
        Record r2 = records[second];
        if(r1 == null) {
            return false;
        } else if(r2 == null) {
            return true;
        } else if(r1.compareTo(r2) < 0) {
            return true;
        } else {
            return false;
        }
    }
}
