package sorter;

public class FinalMerge {

    /*
    public static void main(String[] args) {
     
        // is all the data we need to sort in memory?
        // if so, then this is easy.  Make a stream for
        // each chunk and start the result iterator.
        
        
        
        // if we did not spill anything to HDD, then 
        // we just need to figure out how much memory
        // needs to be allocated for each stream coming 
        // off the ssd.  We only need to have 16K per 
        // stream and then we can leave what ever is still
        // in memory alone and make a memory stream
        
        
        
        // so we ended up spilling to the hdd.  Now we
        // need to make sure we have enough free memory 
        // for each stream that will be merge.  We also 
        // have to make sure we have enough space on the
        // SSD because we are going to read 256K blocks
        // from HDD, but only store 16K in memory, the 
        // other 240K will be staged on the SSD.  Also,
        // we want to keep as many 256KB blocks in memory
        // as possible, that way we don't have to stage
        // those blocks from HDD to SSD and then to memory.
        
        // there should be 1005 ssd streams.
        int ssdStagingRequired = 16 * 1024 * numSsdChunks;
        int hddStagingRequired = 256 * 1024 * numHddChunks;
        
        if(freeMemory >= ssdStagingRequired + hddStagingRequired) {
            // we have enough memory right now to create all the
            // streams for the stuff in memory, as well as the 
            // records stored on ssd and HDD.
        }
        
        if(ssdStagingRequired + hddStagingRequired > totalMemory) {
            // we have more chunks than we can handle without
            // staging HDD data temporarily onto the SSD
            // we will create one more chunk on the HDD that 
            // will free up memory and enough space on the SSD
            // to stage disk chunks.
            
            int hddStagingAvailable = totalMemory - ssdStagingRequired;
            // let x = the number of 256Kb block we can stage directly in memory
            // then numHddChunks - x be the number that we are staged on ssd.
            // x * 256Kb + (numHddChunks - x) * 16K = hddStagingAvailable
            // since we are going to have to free up memory and ssd space
            // we will end up making one more HDD chunk, that stores these
            // chunks. So numHddChunks will be one larger.
            // we will let hddChunksPrime = numHddChunks + 1
            // x * 256Kb + (hddChunksPrime - x) * 16K = hddStagingAvailable
            // x * 16 + (hddChunksPrime - x) = hddStagingAvailable / 16Kb
            // x * 15 = (hddStagingAvailable / 16Kb) - hddChunksPrime;
            // x = ((hddStagingAvailable / 16384) - hddChunksPrime) / 15;
            int hddChunksPrime = numHddChunks + 1;
            int hddNotStaged = ((hddStagingAvailable / 16384) - hddChunksPrime) / 15;
            int hddStagedChunks = hddChunksPrime - hddNotStaged;
            // so on the sdd we need 240Kb of free space for each hdd chunk 
            // that we are going to be staging in the ssd (16Kb gets put in memory)
            
            
            
        }
        
        /

    }
    */

}
