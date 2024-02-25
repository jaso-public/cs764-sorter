package sorter;

import java.util.Random;

/**
 * This class randomly generates records of a certain size and count filled with random numbers
 */
public class RandomGenerator implements Provider {

    // the desired number of records to generate
    public final long count;
    // the size of each individual record
    public final int size;
    
    private long generated = 0;
    private Random rng = new Random();
    
    public RandomGenerator(long count, int size) {
        this.count = count;
        this.size = size;
    }

    /**
     * Continues to return the next record or null if count has been reached
     * Fills each record with random numbers
     * @return the next generated record or null
     */

    @Override
    public Record next() {
        if(generated >= count) return null;
        byte[] record = new byte[size];
        rng.nextBytes(record);
        generated++;
        return new Record(record);
    }

}
