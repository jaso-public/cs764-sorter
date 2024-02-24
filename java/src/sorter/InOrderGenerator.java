package sorter;

import java.nio.ByteBuffer;
import java.util.Random;

public class InOrderGenerator implements Provider {

    public final long count;
    public final int size;
    
    private long generated = 0;
    private Random rng = new Random();
    
    public InOrderGenerator(long count, int size) {
        this.count = count;
        this.size = size;
    }

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
