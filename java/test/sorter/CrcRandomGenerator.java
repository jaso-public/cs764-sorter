package sorter;

import java.nio.ByteBuffer;
import java.util.Random;
import java.util.zip.CRC32;

/**
 * This class randomly generates records of a certain size and count filled with random numbers
 */
public class CrcRandomGenerator implements Provider {

    // the desired number of records to generate
    public final long count;
    // the size of each individual record
    public final int size;
    
    private final CRC32 crc = new CRC32();
    
    private long generated = 0;
    private Random rng = new Random();
    
    public CrcRandomGenerator(long count, int size) {
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
        crc.reset();
        crc.update(record, 0, size-4);
        ByteBuffer buffer = ByteBuffer.wrap(record);
        buffer.putInt(size-4, (int)crc.getValue());
        generated++;
        return new Record(record);
    }
    
    static void verifyCrc(Record rec) {
        if(rec==null) return;
        CRC32 crc = new CRC32();
        crc.update(rec.data, 0, rec.data.length-4);
        ByteBuffer buffer = ByteBuffer.wrap(rec.data);
        int value = buffer.getInt(rec.data.length-4);
        int computed = (int) crc.getValue();
        if(value != computed) throw new RuntimeException("record crc mismatch");
    }

}
