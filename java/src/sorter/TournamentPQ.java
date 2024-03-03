package sorter;

public class TournamentPQ implements Provider {

    private final Provider[] providers;
    private final Record[] records;
    private final int[] losers;
    private final int size;
    
    
    public TournamentPQ(Provider[] prov) {
        providers = prov;
        
        // the number of record providers.
        size = providers.length;
        
        // create and fill the records array
        this.records = new Record[size];
        for(int i=0 ; i<providers.length ; i++) {
            records[i] = providers[i].next();
            System.out.println(i +" "+records[i].getKey());
        }
        
        losers = new int[size];
        int[] winners = new int[size];
        for(int match=size-1 ; match>0 ; match--) {
            int h1 = match * 2;
            int h2 = h1 + 1;
            if(h1>=size) h1 = h1-size; else h1 = winners[h1];
            if(h2>=size) h2 = h2-size; else h2 = winners[h2];
 
            if(firstWins(h1, h2)) {
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
        int match = (provider + size) / 2;
        
        int winner = provider;
        while(match > 0) {
            if(firstWins(losers[match], winner)) {
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
    private boolean firstWins(int first, int second) {
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
