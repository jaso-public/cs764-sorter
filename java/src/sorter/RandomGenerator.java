package sorter;

import java.util.Random;

/**
 *
 */
public class RandomGenerator implements Provider {

    public final long count;
    public final int size;
    
    private long generated = 0;
    private Random rng = new Random();
    
    public RandomGenerator(long count, int size) {
        this.count = count;
        this.size = size;
    }


    @Override
    public Record next() {
        if(generated >= count) return null;
        byte[] record = new byte[size];
        rng.nextBytes(record);
        generated++;
        return new Record(record);
    }

}
