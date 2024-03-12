package sorter;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class SorterTest {

    @Test
    void testSmallSort() {
        
        int recordSize = 100;
        int recordCount = 10;
        
        String test = "testSmallSort: ";
        
        Provider generator = new RandomGenerator(recordCount, recordSize);
        Printer printer1 = new Printer(generator, test+"from generator");
        Witness lower = new Witness(printer1);
        Sorter sorter = new Sorter(new SorterConfig(), lower, recordSize);
        Witness upper = new Witness(sorter);
        Printer printer2 = new Printer(upper, test+"from sorter");
        Consumer consumer = new Consumer(printer2);
        consumer.consume();
        
        assertEquals(recordCount, lower.getCount(), "The count of the lower witness was " + lower.getCount() + " but should have been 10");
        assertEquals(recordCount, upper.getCount(), "The count of the upper witness was " + upper.getCount() + " but should have been 10");
        assertFalse(lower.isSorted(),  "The lower witness should not have been sorted but was");
        assertTrue(upper.isSorted(), "The upper witness was not sorted but should have been");
        assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper but should have");
    }

    @Test
    void testAllMemory() {
        
        int recordSize = 1000;
        int recordCount = 90000;
        
        @SuppressWarnings("unused")
        String test = "testAllMemory: ";
        
        Provider generator = new RandomGenerator(recordCount, recordSize);
        Witness lower = new Witness(generator);
        Sorter sorter = new Sorter(new SorterConfig(), lower, recordSize);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        assertEquals(recordCount, lower.getCount(), "The count of the lower witness was " + lower.getCount() + " but should have been "+recordCount);
        assertEquals(recordCount, upper.getCount(), "The count of the upper witness was " + upper.getCount() + " but should have been "+recordCount);
        assertFalse(lower.isSorted(),  "The lower witness should not have been sorted but was");
        assertTrue(upper.isSorted(), "The upper witness was not sorted but should have been");
        assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper but should have");
    }

    @Test
    void testSpillToSsdFewBlocks() {
        
        int recordSize = 1024;
        int recordCount = 1024*100;
        
        @SuppressWarnings("unused")
        String test = "testSpillToSsdFewBlocks: ";
        
        Provider generator = new RandomGenerator(recordCount, recordSize);
        Witness lower = new Witness(generator);
        Sorter sorter = new Sorter(new SorterConfig(), lower, recordSize);
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


    @Test
    void testSpillToSsd() {
        
        int recordSize = 1000;
        int recordCount = 900000;
        
        @SuppressWarnings("unused")
        String test = "testSpillToSsd: ";
        
        Provider generator = new RandomGenerator(recordCount, recordSize);
        Witness lower = new Witness(generator);
        Sorter sorter = new Sorter(new SorterConfig(), lower, recordSize);
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

    @Test
    void testSpillToHdd() {
        
        int recordSize = 1000;
        int recordCount = 19000;
        
        @SuppressWarnings("unused")
        String test = "testSpillToSsd: ";
        
        SorterConfig cfg = new SorterConfig();
        cfg.ssdStorageSize = 0*1024*1024;
        cfg.memoryBlockCount = 10;
        
        Provider generator = new RandomGenerator(recordCount, recordSize);
        Witness lower = new Witness(generator);
        Sorter sorter = new Sorter(cfg, lower, recordSize);
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
