package sorter;

public class StagingProvider implements Provider {
    
    
    private final StagingConfig cfg;
    

    private long storageOffset = 0;
    private long storageRemaining = 0;
    
    private long stagingOffset = 0;
    private long stagingRemaining;   
    
    private int bufferOffset = 0;
    private int bufferRemaining = 0;

    private long nextRecord = 0;
  
    
    
    
public StagingProvider(StagingConfig cfg) {
        this.cfg = cfg;
       
        assert(cfg.transferLength >= cfg.bufferLength + cfg.stagingLength);
        assert(cfg.bufferStartOffset + cfg.bufferLength <= cfg.buffer.length);

        storageRemaining = cfg.recordCount * cfg.recordSize;
    }



    @Override
    public Record next() {
        if(nextRecord >= cfg.recordCount) return null;
        byte[] data = new byte[cfg.recordSize];
        int recordRemaining = cfg.recordSize;
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
                    int sizeToRead = minSize(cfg.bufferLength + cfg.stagingLength, storageRemaining);
                    cfg.storage.read(cfg.storageStartOffset + storageOffset, cfg.transferBuffer, cfg.transferStartOffset, sizeToRead);
                    storageOffset += sizeToRead;
                    storageRemaining -= sizeToRead;
                    
                    if(sizeToRead <= cfg.bufferLength) {
                        // this must be the final chunk on the HDD. 
                        // It is small enough to fit in the buffer.
                        System.arraycopy(cfg.transferBuffer, cfg.transferStartOffset, cfg.buffer, cfg.bufferStartOffset, sizeToRead);
                        stagingOffset = 0;
                        stagingRemaining = 0;
                        bufferOffset = 0;
                        bufferRemaining = sizeToRead;
                   } else {
                        // we need to put the beginning of the transfer buffer into our buffer,
                        // and the rest of the data needs to be written to the staging area
                        System.arraycopy(cfg.transferBuffer, cfg.transferStartOffset, cfg.buffer, cfg.bufferStartOffset, cfg.bufferLength);
                        cfg.staging.write(cfg.stagingStartOffset, cfg.transferBuffer, cfg.transferStartOffset + cfg.bufferLength, sizeToRead - cfg.bufferLength);
                        stagingOffset = 0;
                        stagingRemaining = sizeToRead - cfg.bufferLength;
                        bufferOffset = 0;
                        bufferRemaining = cfg.bufferLength;
                    }
                } else {
                    // there is data available in the staging area, lets read it.
                    int sizeToRead = minSize(cfg.bufferLength, stagingRemaining);
                    cfg.staging.read(cfg.stagingStartOffset + stagingOffset, cfg.buffer, cfg.bufferStartOffset, sizeToRead);
                    stagingOffset += sizeToRead;
                    stagingRemaining -= sizeToRead;
                    bufferOffset = 0;
                    bufferRemaining = sizeToRead;
                }
            }
            int sizeToCopy = minSize(recordRemaining, bufferRemaining);
            System.arraycopy(cfg.buffer, cfg.bufferStartOffset + bufferOffset, data, recordOffset, sizeToCopy);
            recordOffset += sizeToCopy;
            recordRemaining -= sizeToCopy;
            bufferOffset += sizeToCopy;
            bufferRemaining -= sizeToCopy;           
        }
    }
    
    private static int minSize(long size1, long size2) {
        long result = Math.min(size1, size2);
        if(result>Integer.MAX_VALUE) throw new RuntimeException("sizes too big");
        return (int)result;
    }
}
