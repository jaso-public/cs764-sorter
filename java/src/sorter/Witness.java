package sorter;

public class Witness implements Provider {
    
    public final Provider source;
    
    private long count = 0;
    private long crc = 0;
    private Long lastKey = null;
    private boolean isSorted = true;
    
    public Witness(Provider source) {
        this.source = source;
    }

    @Override
    public Record next() {
        Record result = source.next();
        if(result == null) return null;
        
        if(isSorted) {
            long key = result.getKey();
            if(lastKey!=null) {
                if(lastKey>key) isSorted = false;
            }
            lastKey = key;
        }
        
        count++;
        crc ^= result.getCrc();
        return result;
    }

    public long getCount() {
        return count;
    }

    public long getCrc() {
        return crc;
    }

    public boolean isSorted() {
        return isSorted;
    }
}
