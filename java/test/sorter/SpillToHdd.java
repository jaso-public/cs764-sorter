package sorter;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class SpillToHdd {
    
    @Test
    void testSpillToHdd() {
        
        int recordSize = 1000;
        int recordCount = 19000;
        
        @SuppressWarnings("unused")
        String test = "testSpillToHdd: ";
        
        SorterConfig cfg = new SorterConfig();
        cfg.ssdStorageSize = 2*1024*1024;
        cfg.memoryBlockCount = 10;
        
        Provider generator = new CrcRandomGenerator(recordCount, recordSize);
        Witness lower = new Witness(generator);
        Sorter sorter = new Sorter(cfg, lower);
        Witness upper = new Witness(sorter);
        Printer p = new Printer(upper, test);
        
        while(true) {
            Record record = p.next();
            if(record == null) break;
            CrcRandomGenerator.verifyCrc(record);
        }
      
        sorter.printStats();
        
        assertEquals(recordCount, lower.getCount(), "The count of the lower witness was " + lower.getCount() + " but should have been "+recordCount);
        assertEquals(recordCount, upper.getCount(), "The count of the upper witness was " + upper.getCount() + " but should have been "+recordCount);
        assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper but should have");
        assertFalse(lower.isSorted(),  "The lower witness should not have been sorted but was");
        assertTrue(upper.isSorted(), "The upper witness was not sorted but should have been");
    }

}
