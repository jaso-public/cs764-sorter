package sorter;

import java.util.ArrayList;

public class Sorter implements Provider {
    
    private final SorterConfig cfg;
    
    private final Provider sortedProvider;

    private long ssdOffset;
    private long ssdRemaining;
    private long hddOffset;    
 
    private final byte[] buffer;
    private int lastMemoryRun;
    
    private ArrayList<Run> memoryRuns = new ArrayList<>();
    private ArrayList<Run> ssdRuns = new ArrayList<>();
    private ArrayList<Run> hddRuns = new ArrayList<>();
    
    
    public Sorter(SorterConfig cfg, Provider source) {
        this.cfg = cfg;
             
        // as we write data to the ssd, we will record how much free
        // space is remaining on the ssd.  Initially the entire ssd
        // is consider free and we can start writing from the beginning
        // of the ssd.
        ssdOffset = 0;
        ssdRemaining = cfg.ssdStorageSize;
        
        // we can consider the hdd to have infinite storage so there
        // is no equivalent hddRemaining variable like there is for
        // the ssd, but we do have hhdOffset, which is the location 
        // where the next runs will be written to the hdd.
        hddOffset = 0;
        
        
        // this is the buffer that we get to use for the sorting run.
        // our config breaks it blocks and then the number of block.
        // the block size, should be considered our RAM cache size.
        // for this project, it is 1MB, which is the size of our initial 
        // runs.  Since out block size is 1MB and we are allowed 100MB
        // of memory, we will have 100 of these blocks.  This memory
        // is allocated as a single chunk of memory.
        this.buffer = new byte[cfg.memoryBlockSize * cfg.memoryBlockCount];
        
        // as we create the initial runs, we will store them in memory.  
        // These runs are stored in the buffer, we will treat the buffer
        // like a stack.  The first run will be stored at end of the buffer
        // (the beginning offset will bebuffer.length - cfg.memoryBlockSize)
        // and each subsequent memory run will be stored at an offset 
        // cfg.memoryBlockSize bytes before the previous one.  Since we
        // reserve the very first (offset=0) block as the staging area for 
        // the records, we can only store 99 memory runs, once we have that 
        // many, we have to flush some memory runs to the ssd. After flushing
        // the lastMemoryRun will be increased by cfg.memoryBlockSize times
        // the number of runs flushed.
        lastMemoryRun = buffer.length;
        
        this.sortedProvider = startSort(source);
    }
    
    public Sorter(Provider source) {
        this(new SorterConfig(), source);
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

    private Provider startSort(Provider source) {
        Record.resetCompareCount();
                
        // if the provider returns null right away then there are
        // no records so we can just return an EmptyProvider.
        Record firstRecord = source.next();
        if(firstRecord == null) return new EmptyProvider();
        
        int recordSize = firstRecord.data.length;
        
        int maxRecordsPerRun = cfg.memoryBlockSize / recordSize;
        
        SingleProvider[] singles = new SingleProvider[maxRecordsPerRun];
        for(int i=0 ; i<maxRecordsPerRun ; i++) singles[i] = new SingleProvider();
        
        int count = 0;
        singles[count++].reset(firstRecord);
        
        boolean endReached = false;
        while(!endReached) {
            while(count < maxRecordsPerRun) {
                Record r = source.next();
                if(r == null) {
                    endReached = true;
                    break;
                }
                singles[count++].reset(r);     
            }
            
            if(count > 0) {
                // find the buffer that we are going to fill.
                if(lastMemoryRun == cfg.memoryBlockSize) makeFreeSpace(recordSize);                        
                
                lastMemoryRun -= cfg.memoryBlockSize;
                                
                TournamentPQ pq = new TournamentPQ(singles, count);
                for(int i=0 ; i<count ; i++) {
                    Record r = pq.next();
                    r.store(buffer, lastMemoryRun + i * recordSize);
                }
                memoryRuns.add(new Run(count, lastMemoryRun));
            }  
            count = 0;
        }
         
        // there had better be at least one run to merge.
        assert(memoryRuns.size() + ssdRuns.size() + hddRuns.size() > 0);
 
        // see if we can do the final merge with the memory we have.
        // i.e not too many runs and no need to stage hdd runs to ssd
        int memoryRequired = ssdRuns.size() * cfg.ssdReadSize + (hddRuns.size() + 1) * cfg.hddReadSize;
        if(memoryRequired < cfg.memoryBlockCount * cfg.memoryBlockSize) {
            if(memoryRequired > lastMemoryRun) {
                int toRelease = (memoryRequired - lastMemoryRun + cfg.memoryBlockSize - 1) / cfg.memoryBlockSize;
                releaseMemory(toRelease, recordSize);
            }
            
            Provider[] providers = new Provider[memoryRuns.size() + ssdRuns.size() + hddRuns.size()];
            int index = 0;
            
            for(Run run : memoryRuns) {
                providers[index++] = new MemoryProvider(buffer, run.offset, run.numRecords, recordSize);
            }     
            
            // start using the memory from the beginning of the buffer to stage data from the ssd/hdd.
            int offset = 0;

            for(Run run : hddRuns) {
                providers[index++] = new StorageProvider(recordSize, run.numRecords, cfg.hddDevice, run.offset, buffer, offset, cfg.hddReadSize);
                offset += cfg.hddReadSize;
            }

            for (Run run : ssdRuns) {
                providers[index++] = new StorageProvider(recordSize, run.numRecords, cfg.ssdDevice, run.offset, buffer, offset, cfg.ssdReadSize);
                offset += cfg.ssdReadSize;
            }

            return new TournamentPQ(providers, index);
        }
         
        // we did not have enough memory to do the final merge, so lets flush all of our memory
        // runs and use all the memory to stage the final merge run.
        releaseMemory(memoryRuns.size(), recordSize);        
        
        

        // there are two constraints that we have to worry about now:
        // 1. do we have enough free space on the ssd to do the staging?
        // 2. do we have too many runs to merge in the final pass?
        
        
        // max number of merge runs that can be merged using cfg.ssdReadSize chunk sized memory for each run 
        // Note we reserve one cfg.hddReadSize block of memory to transfer data from the hdd back to the ssd
        int maxMergeRuns = ((cfg.memoryBlockCount * cfg.memoryBlockSize) - cfg.hddReadSize) / cfg.ssdReadSize;
        int runsToMergeForCount = ssdRuns.size() + hddRuns.size() - maxMergeRuns;
        
        // figure out how much space we need for staging hdd data
        long stagingRequired = (hddRuns.size() + 1) * (cfg.hddReadSize - cfg.ssdReadSize);
        int runsToMergeForSpace = 0;
        for(Run run : ssdRuns) {
            if(run.offset > stagingRequired) break;
            runsToMergeForSpace++;
        }
        
        int runsToMerge = Math.max(runsToMergeForSpace, runsToMergeForCount);

        Provider[] providers = new Provider[runsToMerge];
         
        long recordCount = 0;
        for(int i=0 ; i<runsToMerge ; i++) {
            Run run = ssdRuns.remove(0);
            recordCount += run.numRecords;
            int offset = cfg.memoryBlockSize + i * cfg.ssdReadSize; 
            providers[i] = new StorageProvider(recordSize, run.numRecords, cfg.ssdDevice, run.offset, buffer, offset, cfg.ssdReadSize);    
        }
        
        Provider provider = new TournamentPQ(providers, runsToMerge);
        storeRun(provider, recordCount, recordSize);
        
        providers = new Provider[ssdRuns.size() + hddRuns.size()];
        int index = 0;
        int memoryOffset = cfg.memoryBlockSize;
        
        
        for(int i=0 ; i<hddRuns.size(); i++) {
            Run run = hddRuns.get(i);
            
            StagingConfig stagingCfg = new StagingConfig();
            stagingCfg.recordSize = recordSize;
            stagingCfg.recordCount = run.numRecords;
            stagingCfg.storage = cfg.hddDevice;
            stagingCfg.storageStartOffset = run.offset;
            stagingCfg.staging = cfg.ssdDevice;
            stagingCfg.stagingStartOffset = i * (cfg.hddReadSize - cfg.ssdReadSize);
            stagingCfg.stagingLength = cfg.hddReadSize - cfg.ssdReadSize;
            stagingCfg.buffer = buffer;
            stagingCfg.bufferStartOffset = memoryOffset;
            stagingCfg.bufferLength = cfg.ssdReadSize;
            stagingCfg.transferBuffer = buffer;
            stagingCfg.transferStartOffset = 0;
            stagingCfg.transferLength = cfg.hddReadSize;
            providers[index++] = new StagingProvider(stagingCfg);
            memoryOffset += cfg.ssdReadSize;
        }
        
        for(Run run : ssdRuns) {
            providers[index++] = new StorageProvider(recordSize, run.numRecords, cfg.ssdDevice, run.offset, buffer, memoryOffset, cfg.ssdReadSize);
            memoryOffset += cfg.ssdReadSize;
        }

        return new TournamentPQ(providers, index);
    }
    
    
    private void makeFreeSpace(int recordSize) {
        long sorted = ssdOffset + hddOffset;
        sorted /= cfg.memoryBlockSize;
        sorted += memoryRuns.size();
        // at this point sorted contains the number of 1MB blocks we have.
       
        int numToMove = (int)(sorted * cfg.fraction); 
        if(numToMove < 1) numToMove = 1;
        
        releaseMemory(numToMove, recordSize);
    }
    
    private void releaseMemory(int numberBuffersToRelease, int recordSize) {
        Provider[] providers = new Provider[numberBuffersToRelease];
        
        long recordCount = 0;
        int index = 0;
        
        while(memoryRuns.size() > 0 && index < numberBuffersToRelease) {
            Run run = memoryRuns.remove(memoryRuns.size()-1);
            providers[index++] = new MemoryProvider(buffer, run.offset, run.numRecords, recordSize);
            recordCount += run.numRecords;
        }
        
        lastMemoryRun += numberBuffersToRelease * cfg.memoryBlockSize;
        
        Provider provider = new TournamentPQ(providers, index);
        storeRun(provider, recordCount, recordSize);
    }
    
    
    private void storeRun(Provider provider, long recordCount, int recordSize) {  
        
        long spaceRequired = recordCount * recordSize;
        
        IoDevice device = null;
        long deviceOffset = 0;
         
        long ssdRequired = roundUp(spaceRequired, cfg.ssdReadSize); 
        if(ssdRequired <= ssdRemaining) {
            device = cfg.ssdDevice;
            deviceOffset = ssdOffset;
            ssdRuns.add(new Run(recordCount, ssdOffset));
            ssdOffset += ssdRequired;
            ssdRemaining -= ssdRequired;
        } else {
            long hddRequired = roundUp(spaceRequired, cfg.hddReadSize); 
            device = cfg.hddDevice;
            deviceOffset = hddOffset;
            hddRuns.add(new Run(recordCount, hddOffset));
            hddOffset += hddRequired;
        }
        
        int bufferOffset = 0;
        int bufferRemaining = cfg.memoryBlockSize;
        while(true) {
            Record r = provider.next();
            if(r==null) break;
            if(bufferRemaining < recordSize) {
                r.storePartial(buffer, bufferOffset, 0, bufferRemaining);
                int leftOver = recordSize-bufferRemaining;
                device.write(deviceOffset, buffer, 0, cfg.memoryBlockSize);
                deviceOffset += cfg.memoryBlockSize;
                r.storePartial(buffer, 0, bufferRemaining, leftOver);
                bufferOffset = leftOver;
                bufferRemaining = cfg.memoryBlockSize - leftOver;                
            } else {
                r.store(buffer, bufferOffset);
                bufferOffset += recordSize;
                bufferRemaining -= recordSize;
            }
        }
        
        // finally write out what ever is left in the buffer.
        device.write(deviceOffset, buffer, 0, bufferOffset);
    }
    
    private long roundUp(long value, long multiple) {
        long quotient = value / multiple;
        if(quotient * multiple == value) return value;
        return (quotient + 1) * multiple;
    }
       
    public void printStats() {
        System.out.println("SSD usage:" + cfg.ssdDevice.stats());
        System.out.println("HDD usage:" + cfg.hddDevice.stats());
        System.out.println("total number of record comparisons:" + Record.getCompareCount());
    }
 }
