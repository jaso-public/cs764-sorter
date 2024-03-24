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
        // creates byes array
        byte[] record = new byte[size];
        // puts next random bytes into array
        rng.nextBytes(record);
        // resets checksum
        crc.reset();
        // updates checksum instance for bytes, 0, bytes length
        crc.update(record, 0, size-4);
        // wraps byte array into a buffer
        ByteBuffer buffer = ByteBuffer.wrap(record);
        // .getValue returns CRC-32 value
        // writes four bytes containing the given int value
        buffer.putInt(size-4, (int)crc.getValue());
        generated++;
        return new Record(record);
    }
    
    static void verifyCrc(Record rec) {
        if(rec==null) return;
        // writes a check sum value
        CRC32 crc = new CRC32();
        crc.update(rec.data, 0, rec.data.length-4);
        // wraps byte array into a buffer
        ByteBuffer buffer = ByteBuffer.wrap(rec.data);
        //read the next four bytes at this buffer’s current position, composing them into an int value according to the current byte order, and then increments the position by four.
        int value = buffer.getInt(rec.data.length-4);
        // gets the computer checksum value
        int computed = (int) crc.getValue();
        if(value != computed) throw new RuntimeException("record crc mismatch");
    }

}
