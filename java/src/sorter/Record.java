package sorter;

import java.nio.ByteBuffer;
import java.util.zip.CRC32;

/**
 * This class contains the record object and operations to perform on individual records
 */
public class Record implements Comparable<Record> {

    // stores the data within a record
    public final byte[] data;
    private static long compareCount = 0;

    public Record(byte[] data) {
        this.data = data;
    }

    // returns a record's key
    public long getKey() {
        ByteBuffer buffer = ByteBuffer.wrap(data);
        return buffer.getLong(0);
    }

    // returns a records checksum value
    public long getCrc() {
        CRC32 crc = new CRC32();
        crc.update(data);
        return crc.getValue();
    }

    @Override
    public int compareTo(Record other) {
        compareCount++;
        return Long.compare(getKey(), other.getKey());
    }

    public void store(byte[] buffer, int offset) {
        System.arraycopy(data,  0,  buffer,  offset,  data.length);        
    }
    
    public void storePartial(byte[] buffer, int offset, int start, int length) {
        System.arraycopy(data,  start,  buffer,  offset,  length);        
    }

    public static void resetCompareCount() {
        compareCount = 0;
    }
    
    public static long getCompareCount() {
        return compareCount;
    }

}
