package sorter;

public class MemoryProvider implements Provider {

    private final byte[] buffer;
    private final int offset;
    private final int recordCount;
    private final int recordSize;
    
    private int nextRecord = 0;
    
    
    public MemoryProvider(byte[] buffer, long offset, long recordCount, int recordSize) {
        this.buffer = buffer;
        this.offset = safeIntCast(offset);
        this.recordCount = safeIntCast(recordCount);
        this.recordSize = recordSize;
    }

    @Override
    public Record next() {
        if(nextRecord >= recordCount) return null;
        byte[] data = new byte[recordSize];
        System.arraycopy(buffer, offset + nextRecord * recordSize,  data,  0,  recordSize); 
        nextRecord++;
        return new Record(data);
    }
    
    private static int safeIntCast(long value) {
        if(value < Integer.MIN_VALUE || value > Integer.MAX_VALUE) {
            throw new RuntimeException("cannot cast long:"+value+" to an integer");
        }
        return (int) value;
    }
}
