package sorter;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileConsumer {

    public final File file;
    public final Provider source;
    
    private BufferedOutputStream bos;
    private long recordCount = 0;
    private int recordSize = 0;

    public FileConsumer(File file, Provider source) {
        this.file = file ;
        this.source = source;        
         
        try {
            bos = new BufferedOutputStream(new FileOutputStream(file));
        } catch (FileNotFoundException e) {
            throw new RuntimeException("open file("+file.getAbsolutePath()+") threw", e); 
        }
    }

    void consume() {
        while(true) {
            Record record = source.next();
            if(record == null) return;
            
            if(recordCount == 0) {
                recordSize = record.data.length;
            } else {
                if(record.data.length != recordSize) {
                    throw new RuntimeException("expected record size:"+recordSize+" got:"+record.data.length);
                }
            }
            
            try {
                bos.write(record.data);
            } catch (IOException e) {
                throw new RuntimeException("write file("+file.getAbsolutePath()+") threw", e); 
            }
        }
    }
    
    public void close() {
        if(bos == null) return;
        try {
            bos.close();
            bos = null;
        } catch(IOException e) {
            throw new RuntimeException("close file("+file.getAbsolutePath()+") threw", e); 
        }
    }

}
