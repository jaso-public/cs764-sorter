package sorter;

import java.nio.ByteBuffer;
import java.util.zip.CRC32;

public class Record {
 
    public final byte[] data;

    public Record(byte[] data) {
        this.data = data;
    }

    public long getKey() {
        ByteBuffer buffer = ByteBuffer.wrap(data);
        return buffer.getLong(8);
    }

    public long getCrc() {
        CRC32 crc = new CRC32();
        crc.update(data);
        return crc.getValue();
    }
}
