package sorter;

public class StagedProvider implements Provider {
    
    private final int recordSize;
    private final long recordCount;
    
    private final IoDevice storage;
    private final long storageStartOffset;
    
    private final IoDevice staging;
    private final long stagingStartOffset;
    private final long stagingLength;

    private final byte[] buffer;
    private final int bufferStartOffset;
    private final int bufferLength;

    private final byte[] transferBuffer;
    private final int transferStartOffset;
    

    private long storageOffset = 0;
    private long storageRemaining = 0;
    
    private long stagingOffset = 0;
    private long stagingRemaining;   
    
    private int bufferOffset = 0;
    private int bufferRemaining = 0;

    private long nextRecord = 0;
    
    
    
public StagedProvider(int recordSize, long recordCount, IoDevice storage, long storageStartOffset, IoDevice staging,
            long stagingStartOffset, long stagingLength, byte[] buffer, int bufferStartOffset, int bufferLength,
            byte[] transferBuffer, int transferStartOffset, int transferLength) {
        this.recordSize = recordSize;
        this.recordCount = recordCount;
        this.storage = storage;
        this.storageStartOffset = storageStartOffset;
        this.staging = staging;
        this.stagingStartOffset = stagingStartOffset;
        this.stagingLength = stagingLength;
        this.buffer = buffer;
        this.bufferStartOffset = bufferStartOffset;
        this.bufferLength = bufferLength;
        this.transferBuffer = transferBuffer;
        this.transferStartOffset = transferStartOffset;
        
        assert(transferLength >= bufferLength + stagingLength);

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
                if(stagingRemaining < 1) {
                    // there is no data in the staging area so go to the HDD to get
                    // a block of data.
                    int sizeToRead = minSize(bufferLength + stagingLength, storageRemaining);
                    storage.read(storageStartOffset + storageOffset, transferBuffer, transferStartOffset, sizeToRead);
                    storageOffset += sizeToRead;
                    storageRemaining -= sizeToRead;
                    
                    if(sizeToRead <= bufferLength) {
                        // this must be the final chunk on the HDD. 
                        // It is small enough to fit in the buffer.
                        System.arraycopy(transferBuffer, transferStartOffset, buffer, bufferStartOffset, sizeToRead);
                        stagingOffset = 0;
                        stagingRemaining = 0;
                        bufferOffset = 0;
                        bufferRemaining = sizeToRead;
                   } else {
                        // we need to put the beginning of the transfer buffer into our buffer,
                        // and the rest of the data needs to be written to the staging area
                        System.arraycopy(transferBuffer, transferStartOffset, buffer, bufferStartOffset, bufferLength);
                        staging.write(stagingStartOffset, transferBuffer, transferStartOffset + bufferLength, sizeToRead - bufferLength);
                        stagingOffset = 0;
                        stagingRemaining = sizeToRead - bufferLength;
                        bufferOffset = 0;
                        bufferRemaining = bufferLength;
                    }
                } else {
                    // there is data available in the staging area, lets read it.
                    int sizeToRead = minSize(bufferLength, stagingRemaining);
                    staging.read(stagingStartOffset + stagingOffset, buffer, bufferStartOffset, sizeToRead);
                    stagingOffset += sizeToRead;
                    stagingRemaining -= sizeToRead;
                    bufferOffset = 0;
                    bufferRemaining = sizeToRead;
                }
            }

            
            int sizeToCopy = minSize(recordRemaining, bufferRemaining);
            System.arraycopy(buffer, bufferStartOffset + bufferOffset, data, recordOffset, sizeToCopy);
            recordOffset += sizeToCopy;
            recordRemaining -= sizeToCopy;
            bufferOffset += sizeToCopy;
            bufferRemaining -= sizeToCopy;           
        }
    }
    
    private int minSize(long size1, long size2) {
        long result = Math.min(size1, size2);
        if(result>Integer.MAX_VALUE) throw new RuntimeException("sizes too big");
        return (int)result;
    }
}
