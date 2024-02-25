package sorter;

import java.nio.ByteBuffer;
import java.util.zip.CRC32;

/**
 * This class contains the record object and operations to preform on individual records
 */
public class Record {

    // stores the data within a record
    public final byte[] data;

    public Record(byte[] data) {
        this.data = data;
    }

    // returns a record's key
    public long getKey() {
        ByteBuffer buffer = ByteBuffer.wrap(data);
        return buffer.getLong(8);
    }

    // returns a records checksum value
    public long getCrc() {
        CRC32 crc = new CRC32();
        crc.update(data);
        return crc.getValue();
    }
}
