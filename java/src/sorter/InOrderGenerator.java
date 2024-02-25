package sorter;

import java.nio.ByteBuffer;
import java.util.Random;

/**
 * This class can be used to generate records of a certain size and amount
 */
public class InOrderGenerator implements Provider {

    // represents total number of records to generate
    public final long count;
    // represents the size of the records
    public final int size;
    // stores actual number of records currently generated
    private long generated = 0;
    private Random rng = new Random();
    
    public InOrderGenerator(long count, int size) {
        this.count = count;
        this.size = size;
    }

    /**
     * Continues to generate a new record in memory until records of the desired count have been generated
     * @return the next record or null if count has been reached
     */
    @Override
    public Record next() {
        if(generated >= count) return null;
        byte[] data = new byte[size];
        rng.nextBytes(data);
        ByteBuffer buffer = ByteBuffer.wrap(data);
        buffer.putLong(8, generated);
        generated++;
        return new Record(data);
    }

}
