package sorter;

import java.io.File;
import java.io.IOException;

import org.junit.Assert;
import org.junit.jupiter.api.Test;

class StorageProviderTest {

    public void doTest(int recordSize, long recordCount, int stagingLength, int bufferLength) throws IOException {
        RandomGenerator rg = new RandomGenerator(recordCount, recordSize);
        Witness before = new Witness(rg);
        
        File storageFile = File.createTempFile("storage", ".tmp");
        storageFile.deleteOnExit();
        IoDevice storage = new IoDevice(storageFile);
        
        long storageOffset = 0;
        while(true) {
            Record rec = before.next();
            if(rec==null) break;
            storage.write(storageOffset, rec.data, 0, rec.data.length);
            storageOffset += rec.data.length;            
        }
                
        byte[] memory = new byte[10*1024*1024]; // 10MB
              
        
        long storageStartOffset = 0; // we wrote the records at offset zero        
   
        byte[] buffer = memory;
        int bufferStartOffset = 20;

        
        StorageProvider sp = new StorageProvider(
                recordSize,
                recordCount,
                storage,
                storageStartOffset,
                buffer,
                bufferStartOffset,
                bufferLength);
        
         
        Witness after = new Witness(sp);
        Consumer c = new Consumer(after);
        c.consume();
        
        Assert.assertEquals(before.getCount(), after.getCount());
        Assert.assertEquals(before.getCrc(), after.getCrc());
     }
    
    

    @Test
    void testSmall() throws IOException {
        doTest(123,50,564,2048);
     }

    @Test
    void testMedium() throws IOException {
        doTest(12003,50,1024,2048);
     }

}
