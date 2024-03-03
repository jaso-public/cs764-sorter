package sorter;

import java.util.ArrayList;
import java.util.List;

import org.junit.Assert;
import org.junit.jupiter.api.Test;

class TournamentPQTest {

    void doTest(int numProviders) {
        int numItemsPerList = 10;
    
        Provider p = new InOrderGenerator(numProviders * numItemsPerList, 16);
        Witness before = new Witness(p);
        
        @SuppressWarnings("unchecked")
        List<Record>[] lists = new List[numProviders];
        
        for(int i=0; i<numProviders ; i++) {
            lists[i] = new ArrayList<Record>(numItemsPerList);
        }
        
        for(int j=0 ; j<numItemsPerList ; j++) {
            for(int i=numProviders-1 ; i>=0 ; i--) {
                lists[i].add(before.next());
            }
        }
        
        Provider[] providers = new Provider[numProviders];
        for(int i=0; i<numProviders ; i++) {
            providers[i] = new ArrayProvider("Provider-"+i, lists[i].iterator());
        }
        
       
        TournamentPQ pq = new TournamentPQ(providers);
        Witness w = new Witness(pq);
        //Printer pr = new Printer(w, "After Tournament");
        Consumer c = new Consumer(w);
        c.consume();
        
        Assert.assertTrue(w.isSorted());  
        Assert.assertEquals(before.getCrc(), w.getCrc());
    }
    
    @Test
    void testVariousNumberOfProviders() {
        for(int i=1; i<100; i++) {
            doTest(i);
        }
    }


}
