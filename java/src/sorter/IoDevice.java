package sorter;

import java.io.Closeable;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;

public class IoDevice implements Closeable {
    
    private final File file;
    private final RandomAccessFile raf;
    
    private long readCount = 0;
    private long readSize = 0;
    private long writeCount = 0;
    private long writeSize = 0;
    
    

    public IoDevice(File file) {
        try {
            this.file = file;
            this.raf = new RandomAccessFile(file, "rw");
        } catch (IOException e) {
            throw new RuntimeException("open:"+file.getAbsolutePath(), e);
        }
    }

    public void read(long offset, byte[] buffer, int off, int len) {
        try {
            raf.seek(offset);
            raf.readFully(buffer, off, len);
            readCount++;
            readSize += len;
        } catch (IOException e) {
            throw new RuntimeException("read:"+file.getAbsolutePath(), e);
        }
    }

    public void write(long offset, byte[] buffer, int off, int len) {
        try {
            raf.seek(offset);
            raf.write(buffer, off, len);
            writeCount++;
            writeSize += len;
        } catch (IOException e) {
            throw new RuntimeException("write:"+file.getAbsolutePath(), e);
        }        
    }

    public long getReadCount() {
        return readCount;
    }

    public long getReadSize() {
        return readSize;
    }

    public long getWriteCount() {
        return writeCount;
    }

    public long getWriteSize() {
        return writeSize;
    }

    @Override
    public void close() throws IOException {
        raf.close();        
    }

    public String stats() {
        // TODO Auto-generated method stub
        return "read (count="+readCount+" size="+readSize+") write(count="+writeCount+" size="+writeSize+")";
    }
}
