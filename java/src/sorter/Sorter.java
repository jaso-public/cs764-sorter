package sorter;

import java.util.ArrayList;

public class Sorter implements Provider {
    
    private final SorterConfig cfg;
    private final Provider source;
    private final int recordSize;
    
    private final Provider sortedProvider;

    private long ssdOffset = 0;
    private long ssdRemaining = 0;
    private long hddOffset = 0;
    
 
    private final byte[] buffer;
    private int lastMemoryRun;
    
    ArrayList<Run> memoryRuns = new ArrayList<>();
    ArrayList<Run> ssdRuns = new ArrayList<>();
    ArrayList<Run> hddRuns = new ArrayList<>();
    
    
    public Sorter(SorterConfig cfg, Provider source, int recordSize) {
        this.cfg = cfg;
        this.source = source;
        this.recordSize = recordSize;
             
        
        ssdRemaining = cfg.ssdStorageSize;
        
        this.buffer = new byte[cfg.memoryBlockSize * cfg.memoryBlockCount];
        lastMemoryRun = buffer.length;
        
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
        Record.resetCompareCount();
        
        int maxRecordsPerRun = cfg.memoryBlockSize / recordSize;
        
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
                if(lastMemoryRun == cfg.memoryBlockSize) makeFreeSpace();                        
                
                lastMemoryRun -= cfg.memoryBlockSize;
                                
                TournamentPQ pq = new TournamentPQ(singles, recordCount);
                for(int i=0 ; i<recordCount ; i++) {
                    Record r = pq.next();
                    r.store(buffer, lastMemoryRun + i * recordSize);
                }
                memoryRuns.add(new Run(recordCount, lastMemoryRun));
            }  
        }
         
        // if there was nothing to sort then return an empty provider.
        if(memoryRuns.size() == 0 && ssdRuns.size() == 0 && hddRuns.size() == 0) {
            return new EmptyProvider();
        }

        // see if we can do the final merge with the memory we have.
        // i.e not too many runs and no need to stage hdd runs to ssd
        int memoryRequired = ssdRuns.size() * cfg.ssdReadSize + (hddRuns.size() + 1) * cfg.hddReadSize;
        if(memoryRequired < cfg.memoryBlockCount * cfg.memoryBlockSize) {
            if(memoryRequired > lastMemoryRun) {
                int toRelease = (memoryRequired - lastMemoryRun + cfg.memoryBlockSize - 1) / cfg.memoryBlockSize;
                releaseMemory(toRelease);
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
        releaseMemory(memoryRuns.size());        
        
        
//        System.out.println("------------------");
//        System.out.println("memoryRuns.size():"+memoryRuns.size());
//        System.out.println("ssdRuns.size():"+ssdRuns.size());
//        System.out.println("hddRuns.size():"+hddRuns.size());

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
        storeRun(provider, recordCount);
        
        providers = new Provider[ssdRuns.size() + hddRuns.size()];
        int index = 0;
        int memoryOffset = cfg.memoryBlockSize;
        
        
        for(int i=0 ; i<hddRuns.size(); i++) {
            Run run = hddRuns.get(i);
            
            StagedProvider.StagingConfig stagingCfg = new StagedProvider.StagingConfig();
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
            providers[index++] = new StagedProvider(stagingCfg);
            memoryOffset += cfg.ssdReadSize;
        }
        
        for(Run run : ssdRuns) {
            providers[index++] = new StorageProvider(recordSize, run.numRecords, cfg.ssdDevice, run.offset, buffer, memoryOffset, cfg.ssdReadSize);
            memoryOffset += cfg.ssdReadSize;
        }

        return new TournamentPQ(providers, index);
    }
    
    
    private void makeFreeSpace() {
        long sorted = ssdOffset + hddOffset;
        sorted /= cfg.memoryBlockSize;
        sorted += memoryRuns.size();
        // at this point sorted contains the number of 1MB blocks we have.
       
        int numToMove = (int)(sorted * cfg.fraction); 
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
            providers[index++] = new MemoryProvider(buffer, run.offset, run.numRecords, recordSize);
            recordCount += run.numRecords;
        }
        
        lastMemoryRun += numberBuffersToRelease * cfg.memoryBlockSize;
        
        Provider provider = new TournamentPQ(providers, index);
        storeRun(provider, recordCount);
    }
    
    
    private void storeRun(Provider provider, long recordCount) {  
        
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
