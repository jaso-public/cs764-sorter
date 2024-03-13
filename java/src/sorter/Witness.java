package sorter;

/**
 * This class will be utilized to verify the correctness of the records sorting algorithm
 */
public class Witness implements Provider {
    
    public final Provider source;

    // keeps track of all the records returned by next()
    private long count = 0;
    private long crc = 0;
    private Long lastKey = null;
    private boolean isSorted = true;
    
    public Witness(Provider source) {
        this.source = source;
    }

    /**
     * Returns the next record in the list and checks that each record key is sorted
     * @return next record or null if no more records exists
     */
    @Override
    public Record next() {
        Record result = source.next();
        if(result == null) return null;
        // checks that keys are sorted; sets isSorted to false if not
        if(isSorted) {
            long key = result.getKey();
            if(lastKey!=null) {
                if(lastKey>key) isSorted = false;
            }
            lastKey = key;
        }
        count++;
        // computes checksum value of record
        crc ^= result.getCrc();
        return result;
    }

    // returns the number of records returned by next()
    public long getCount() {
        return count;
    }

    // returns the checksum value
    public long getCrc() {
        return crc;
    }
    // returns whether the record key's/indexes have been sorted up to this point
    public boolean isSorted() {
        return isSorted;
    }

    @Override
    public String toString() {
        return "Witness [count=" + count + ", crc=" + crc + ", isSorted=" + isSorted + "]";
    }
    
    
}
