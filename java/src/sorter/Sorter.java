package sorter;

import java.io.File;
import java.util.ArrayList;

public class Sorter implements Provider {
    
    private float percentage = 0.005F;

    private final String ssdPath = "sddStaging.tmp";
    private IoDevice ssdDevice = null;    
    private long ssdOffset = 0;
    public final int ssdReadSize = 16 * 1024;
    private long ssdRemaining = 10L * 1024 * 1024 * 1024;
   
    
    private final String hddPath = "hddStaging.tmp";
    private IoDevice hddDevice = null;
    private long hddOffset = 0;
    public final int hddReadSize = 256 * 1024;

    private final Provider source;
    private final Provider sortedProvider;

     
    private final int recordSize;
    
    
    // the first 1MB will always be our "work" area.
    // when we are building runs we will get 1MB from the source records.
    // when we are merging intermediate runs we will use this to stage 
    // before writing it to the device.
    
 
    private final int bufferPageSize = 1024 * 1024;
    private final byte[] buffer  = new byte[100 * bufferPageSize]; // the rest of the memory we get to use
    private final ArrayList<Integer> freeOffsets = new ArrayList<Integer>();
    
    
    ArrayList<Run> memoryRuns = new ArrayList<>();
    ArrayList<Run> ssdRuns = new ArrayList<>();
    ArrayList<Run> hddRuns = new ArrayList<>();
    
    
    public Sorter(Provider source, int recordSize) {
        this.source = source;
        this.recordSize = recordSize;
        
        for(int i=1 ; i<100 ; i++) freeOffsets.add(i*bufferPageSize);
        this.sortedProvider = startSort();
    }

    class Run {
        long numRecords;
        long offset;
        
        public Run(long numRecords, long offset) {
            this.numRecords = numRecords;
            this.offset = offset;
        }
    }
    
    @Override
    public Record next() {
        return sortedProvider.next();
    }

    private Provider startSort() {
        int maxRecordsPerRun = bufferPageSize / recordSize;
        
        SingleProvider[] singles = new SingleProvider[maxRecordsPerRun];
        for(int i=0 ; i<maxRecordsPerRun ; i++) singles[i] = new SingleProvider();
        
        boolean endReached = false;
        while(!endReached) {
            int recordCount = 0;
            while(recordCount < maxRecordsPerRun) {
                Record r = source.next();
                if(r == null) {
                    endReached = true;
                    break;
                }
                singles[recordCount++].reset(r);     
            }
            
            if(recordCount > 0) {
                // find the buffer that we are going to fill.
                int bufferOffset = getFreePage();
                
                TournamentPQ pq = new TournamentPQ(singles, recordCount);
                for(int i=0 ; i<recordCount ; i++) {
                    Record r = pq.next();
                    r.store(buffer, bufferOffset + i * recordSize);
                }
                memoryRuns.add(new Run(recordCount, bufferOffset));
            }  
        }
         
        // if there was nothing to sort the return an empty provider.
        if(memoryRuns.size() == 0 && ssdRuns.size() == 0 && hddRuns.size() == 0) {
            return new EmptyProvider();
        }

                
        int memoryRequired = ssdRuns.size() * ssdReadSize + hddRuns.size() * hddReadSize;

        // if the memory required to stage the ssd and hdd can fit without having
        // to free up any memory, then do it.
        if(memoryRequired <= freeOffsets.size() * bufferPageSize) {
            // we can just do the merge with the memory we have.
            Provider[] providers = new Provider[memoryRuns.size() + ssdRuns.size() + hddRuns.size()];
            
            int index = 0;
            for(Run run : memoryRuns) {
                providers[index++] = new MemoryProvider(buffer, safeIntCast(run.offset), safeIntCast(run.numRecords), recordSize);
            }          

            int freeStart = 0; // the start of the free block of memory
            int freeRem = 0;   // how many bytes are still available for holding staged data
            int freeOff = 0;   // the offset into the block that we will use to stage data. 
            
            for(Run run : hddRuns) {
                if(freeRem < hddReadSize) {
                    freeStart = getFreePage();
                    freeRem = bufferPageSize;
                    freeOff = 0;
                }
                freeRem -= hddReadSize;
                freeOff += hddReadSize;
                providers[index++] = new StorageProvider(recordSize, run.numRecords, hddDevice, run.offset, buffer, freeStart + freeOff, hddReadSize);
            }

            for(Run run : ssdRuns) {
                if(freeRem < ssdReadSize) {
                    freeStart = getFreePage();
                    freeRem = bufferPageSize;
                    freeOff = 0;
                }
                freeRem -= ssdReadSize;
                freeOff += ssdReadSize;
                providers[index++] = new StorageProvider(recordSize, run.numRecords, ssdDevice, run.offset, buffer, freeStart + freeOff, ssdReadSize);
            }
 
            return new TournamentPQ(providers, index);
        }
        
        // flush all the memory buffers to an IoDevice
        releaseMemory(99);
        
        // now make room to stage runs on the hdd that need to be staged on the ssd
        if(hddRuns.size() > 0) {
        
            // figure out how much space we need for staging hdd data back to the ssd.
            long ssdStagingRequired = (hddReadSize - ssdReadSize) * (hddRuns.size() + 1);
            int mergeCount = 0;
            for(int i=0 ; i<ssdRuns.size(); i++) {
                Run run = ssdRuns.get(i);
                if(run.offset > ssdStagingRequired) {
                    mergeCount = i;
                    break;
                }
            }
            
            Provider[] providers = new Provider[mergeCount];
            long recordCount = 0;
            // all memory is free right now so we can just allocate from offset 1
            for(int i=0; i<mergeCount ; i++) {
                Run run = ssdRuns.remove(0);
                recordCount += run.numRecords;
                providers[i] = new StorageProvider(recordSize, run.numRecords, ssdDevice, run.offset, buffer, i*ssdReadSize, ssdReadSize);
            }
            
            Provider mergeStaging = new TournamentPQ(providers, mergeCount);
            storeRun(mergeStaging, recordCount);
        }
        
        Provider[] providers = new Provider[ssdRuns.size() + hddRuns.size()];
        int index = 0;
        int bufferOffset = hddReadSize; // reserve enough memory to read a block from disk and write it back to ssd
        
        for(int i=0 ; i<hddRuns.size(); i++) {
            Run run = hddRuns.get(i);
            
            StagedProvider.StagingConfig cfg = new StagedProvider.StagingConfig();
            cfg.recordSize = recordSize;
            cfg.recordCount = run.numRecords;
            cfg.storage = getHddDevice();
            cfg.storageStartOffset = run.offset;
            cfg.staging = getSsdDevice();
            cfg.stagingStartOffset = i * (hddReadSize - ssdReadSize);
            cfg.stagingLength = hddReadSize - ssdReadSize;
            cfg.buffer = buffer;
            cfg.bufferStartOffset = bufferOffset;
            cfg.bufferLength = ssdReadSize;
            cfg.transferBuffer = buffer;
            cfg.transferStartOffset = 0;
            cfg.transferLength = hddReadSize;
            
            bufferOffset += ssdReadSize;

            providers[index++] = new StagedProvider(cfg);
        }
        
        for(Run run : ssdRuns) {
            providers[index++] = new StorageProvider(recordSize, run.numRecords, ssdDevice, run.offset, buffer, bufferOffset, ssdReadSize);
            System.out.println("created ssd provider:"+index+" offset:"+run.offset+" count:"+run.numRecords);
            bufferOffset += ssdReadSize;
        }

        return new TournamentPQ(providers, index);
     }
    
    int getFreePage() {
        if(freeOffsets.isEmpty()) makeFreeSpace();           
        return freeOffsets.remove(freeOffsets.size()-1);
    }
    
    private void makeFreeSpace() {
        long sorted = ssdOffset + hddOffset;
        sorted /= bufferPageSize;
        sorted += memoryRuns.size();
        // at this point sorted contains the number of 1MB blocks we have.

        
        int numToMove = (int)(sorted * percentage); 
        if(numToMove < 1) numToMove = 1;
        if(numToMove > 99) numToMove = 99;
        
        releaseMemory(numToMove);
    }
    
    private void releaseMemory(int numberBuffersToRelease) {
        Provider[] providers = new Provider[numberBuffersToRelease];
        
        long recordCount = 0;
        int index = 0;
        
        while(memoryRuns.size() > 0 && index < numberBuffersToRelease) {
            Run run = memoryRuns.remove(memoryRuns.size()-1);
            int offset = safeIntCast(run.offset);
            providers[index++] = new MemoryProvider(buffer, offset, safeIntCast(run.numRecords), recordSize);
            recordCount += run.numRecords;
            freeOffsets.add(offset);
        }
        
        Provider provider = new TournamentPQ(providers, index);
        storeRun(provider, recordCount);
    }
    
    
    private void storeRun(Provider provider, long recordCount) {
        System.out.println("storing a run; recordCount="+recordCount);
        printStats();
        
        long spaceRequired = recordCount * recordSize;
        
        IoDevice device = null;
        long deviceOffset = 0;
        
        long ssdRequired = roundUp(spaceRequired, ssdReadSize); 
        if(ssdRequired <= ssdRemaining) {
            device = getSsdDevice();
            deviceOffset = ssdOffset;
            ssdOffset += ssdRequired;
            ssdRemaining -= ssdRequired;
            ssdRuns.add(new Run(recordCount, deviceOffset));
        } else {
            long hddRequired = roundUp(spaceRequired, hddReadSize); 
            device = getHddDevice();
            deviceOffset = hddOffset;
            hddOffset += hddRequired;
            hddRuns.add(new Run(recordCount, deviceOffset));
        }
        
        int bufferOffset = 0;
        int bufferRemaining = bufferPageSize;
        while(true) {
            Record r = provider.next();
            if(r==null) break;
            if(bufferRemaining < recordSize) {
                r.storePartial(buffer, bufferOffset, 0, bufferRemaining);
                int leftOver = recordSize-bufferRemaining;
                device.write(deviceOffset, buffer, 0, bufferPageSize);
                deviceOffset += bufferPageSize;
                r.storePartial(buffer, 0, bufferRemaining, leftOver);
                bufferOffset = leftOver;
                bufferRemaining = bufferPageSize - leftOver;                
            } else {
                r.store(buffer, bufferOffset);
                bufferOffset += recordSize;
                bufferRemaining -= recordSize;
            }
        }
        
        // finally write out what ever is left in the buffer.
        device.write(deviceOffset, buffer, 0, bufferOffset);
    }
    
    private IoDevice getSsdDevice() {
        if(ssdDevice == null) {
            ssdDevice = new IoDevice(new File(ssdPath));   
        }
        return ssdDevice;
    }

    private IoDevice getHddDevice() {
        if(hddDevice == null) {
            hddDevice = new IoDevice(new File(hddPath));   
        }
        return hddDevice;
    }
    
    private long roundUp(long value, long multiple) {
        long quotient = value / multiple;
        if(quotient * multiple == value) return value;
        return (quotient + 1) * multiple;
    }
   
    private int safeIntCast(long value) {
        if(value < Integer.MIN_VALUE || value > Integer.MAX_VALUE) {
            throw new RuntimeException("cannot cast long:"+value+" to an integer");
        }
        return (int) value;
    }
    
    public void printStats() {
        if(ssdDevice == null) {
            System.out.println("never used the SSD device.");
        } else {
            System.out.println("SSD usage:" + ssdDevice.stats());
        }
        if(hddDevice == null) {
            System.out.println("never used the HDD device.");
        } else {
            System.out.println("HDD usage:" + hddDevice.stats());
        }
    }

 }
