package sorter;

import java.io.File;

public class SorterConfig {    
    public float fraction = 0.005F;
    
    public int memoryBlockSize = 1024 * 1024;
    public int memoryBlockCount = 100;

    public IoDevice ssdDevice = new IoDevice(new File("ssdStaging.tmp"));    
    public  int ssdReadSize = 16 * 1024;
    public long ssdStorageSize = 10L * 1024 * 1024 * 1024;
       
    public IoDevice hddDevice = new IoDevice(new File("hddStaging.tmp"));   
    public  int hddReadSize = 256 * 1024;
}
