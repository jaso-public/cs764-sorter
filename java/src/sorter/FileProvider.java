package sorter;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class FileProvider implements Provider {
    
    public final File file;
    public final int recordSize;
    public final long recordCount;
    
    private BufferedInputStream bis;
    private long nextRecord = 0;

    public FileProvider(File file, int recordSize) {
        this.file = file ;
        this.recordSize = recordSize;
        
        long size = file.length();
        if(size % recordSize != 0) {
            throw new RuntimeException("file("+file.getAbsolutePath()+") size("+size+") is not an even multiple of the record size("+size+")");
        }
        
        try {
            bis = new BufferedInputStream(new FileInputStream(file));
        } catch (FileNotFoundException e) {
            throw new RuntimeException("open file("+file.getAbsolutePath()+") threw", e); 
        }
        
        recordCount = size / recordSize;
    }

    @Override
    public Record next() {
        if(nextRecord >= recordCount) return null;
        nextRecord++;
        
        byte[] data = new byte[recordSize];
        
        int offset = 0;
        int remaining = recordSize;
        
        while(remaining > 0) {
            int count = 0;
            try {
                count = bis.read(data, offset, remaining);
            } catch (IOException e) {
                throw new RuntimeException("read file("+file.getAbsolutePath()+") threw", e); 
            }
            
            if(count < 1) {
                throw new RuntimeException("read file("+file.getAbsolutePath()+") return count="+count); 
            }
            offset += count;
            remaining -= count;
        }
        
        return new Record(data);
    }
    
    public void close() {
        if(bis == null) return;
        try {
            bis.close();
            bis = null;
        } catch(IOException e) {
            throw new RuntimeException("close file("+file.getAbsolutePath()+") threw", e); 
        }
    }
}
