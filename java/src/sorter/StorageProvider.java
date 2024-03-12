package sorter;

public class StorageProvider implements Provider {
    
    private final int recordSize;
    private final long recordCount;
    
    private final IoDevice storage;
    private final long storageStartOffset;

    private final byte[] buffer;
    private final int bufferStartOffset;
    private final int bufferLength;


     
    private int bufferOffset = 0;
    private int bufferRemaining = 0;
    
    private long storageOffset = 0;
    private long storageRemaining = 0;

    private long nextRecord = 0;

    

    public StorageProvider(
            int recordSize, 
            long recordCount, 
            IoDevice storage, 
            long storageStartOffset, 
            byte[] buffer,
            int bufferStartOffset, 
            int bufferLength) {
        this.recordSize = recordSize;
        this.recordCount = recordCount;
        this.storage = storage;
        this.storageStartOffset = storageStartOffset;
        this.buffer = buffer;
        this.bufferStartOffset = bufferStartOffset;
        this.bufferLength = bufferLength;
        
        storageRemaining = recordCount * (long)recordSize;
    }

    @Override
    public Record next() {
        if(nextRecord >= recordCount) return null;
        byte[] data = new byte[recordSize];
        int recordRemaining = recordSize;
        int recordOffset = 0;
        
        while(true) {        
            if(recordRemaining < 1) {
                nextRecord++;
                return new Record(data);
            }
            
            if(bufferRemaining < 1) {
                //need to get more bytes from storage
                int sizeToRead = bufferLength;
                if(storageRemaining < sizeToRead) sizeToRead = (int)storageRemaining;
                storage.read(storageStartOffset + storageOffset, buffer, bufferStartOffset, sizeToRead);
                storageOffset += sizeToRead;
                storageRemaining -= sizeToRead;
                bufferOffset = 0;
                bufferRemaining = sizeToRead;                
            }
            
            int sizeToCopy = recordRemaining;
            if(bufferRemaining < sizeToCopy) sizeToCopy = bufferRemaining;
            System.arraycopy(buffer, bufferStartOffset + bufferOffset, data, recordOffset, sizeToCopy);
            recordOffset += sizeToCopy;
            recordRemaining -= sizeToCopy;
            bufferOffset += sizeToCopy;
            bufferRemaining -= sizeToCopy;           
        }
    }    
}
