package sorter;

public class ExpectedCrcWitness implements Provider {
    public final Provider source;
    public final long expectedCrc;
    public final String message;

    // keeps track of all the records returned by next()
    @SuppressWarnings("unused")
    private long count = 0;
    private long crc = 0;
    private Long lastKey = null;
    private boolean isSorted = true;
    
  
    public ExpectedCrcWitness(Provider source, long expectedCrc, String message) {
        this.source = source;
        this.expectedCrc = expectedCrc;
        this.message = message;
    }


    /**
     * Returns the next record in the list and checks that each record key is sorted
     * @return next record or null if no more records exists
     */
    @Override
    public Record next() {
        Record result = source.next();
        if(result == null) {
            if(crc != expectedCrc) {
                throw new RuntimeException("crc mismatch "+message);
            }
            return null;
        }
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


}
