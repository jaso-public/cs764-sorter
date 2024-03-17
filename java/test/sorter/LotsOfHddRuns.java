package sorter;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class LotsOfHddRuns {

    @Test
    void testSpillToLotsOfHddRuns() {
        
        int recordSize = 1000;
        int recordCount = 190000;
        
        @SuppressWarnings("unused")
        String test = "testSpillToLotsOfHddRuns: ";
        
        SorterConfig cfg = new SorterConfig();
        cfg.ssdStorageSize = 100*1024*1024;
        cfg.memoryBlockCount = 10;
        
        Provider generator = new CrcRandomGenerator(recordCount, recordSize);
        Witness lower = new Witness(generator);
        Sorter sorter = new Sorter(cfg, lower);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        sorter.printStats();
        
        assertEquals(recordCount, lower.getCount(), "The count of the lower witness was " + lower.getCount() + " but should have been "+recordCount);
        assertEquals(recordCount, upper.getCount(), "The count of the upper witness was " + upper.getCount() + " but should have been "+recordCount);
        assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper but should have");
        assertFalse(lower.isSorted(),  "The lower witness should not have been sorted but was");
        assertTrue(upper.isSorted(), "The upper witness was not sorted but should have been");
    }

}
