package sorter;



import org.junit.Assert;
import org.junit.jupiter.api.Test;

/**
 * JUnit tests to test that our sorting algorithm is working properly by utilizing the Witness class
 */
class WitnessTest {

    /**
     * Checks that 10 records of size 100 are properly created and sorted with the InOrderGenerator
     */
    @Test
    void testTenInorder() {
        
        Provider generator = new InOrderGenerator(10, 100);
        Witness lower = new Witness(generator);
        NoopSorter sorter = new NoopSorter(lower);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(lower.getCount(), upper.getCount(), "The count of the lower witness did not equal the count of the upper");
        Assert.assertEquals(10, upper.getCount(), "The count upper witness was " + upper.getCount() + " but should have been 10");
        Assert.assertTrue(upper.isSorted(), "The upper witness should have been sorted, but was not");
        Assert.assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper but should have");
    }

    /**
     * Checks that DropFirst can drop the first record and that the sorting algorithm properly worked
     */
    @Test
    void testDropOne() {
        
        Provider generator = new InOrderGenerator(10, 100);
        Witness lower = new Witness(generator);
        DropFirst dropper = new DropFirst(lower);
        NoopSorter sorter = new NoopSorter(dropper);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(10, lower.getCount(),  "The count lower witness was " + lower.getCount() + " but should have been 10");
        Assert.assertEquals(9, upper.getCount(), "The count upper witness was " + upper.getCount() + " but should have been 9");
        Assert.assertTrue(lower.isSorted(),  "The lower witness should have been sorted, but was not");
        Assert.assertTrue(upper.isSorted(),  "The upper witness should have been sorted, but was not");
        Assert.assertNotEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness equaled the checksum of the upper but should not have");
    }

    /**
     * Checks that 10 records of size 100 are properly created and sorted with the RandomGenerator
     */
    @Test
    void testRandomOrder() {
        Provider generator = new RandomGenerator(10, 100);
        Witness lower = new Witness(generator);
        NoopSorter sorter = new NoopSorter(lower);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(10, lower.getCount(),  "The count lower witness was " + lower.getCount() + " but should have been 10");
        Assert.assertEquals(10, upper.getCount(),  "The count upper witness was " + upper.getCount() + " but should have been 10");
        Assert.assertFalse(lower.isSorted(),  "The lower witness should have been sorted, but was not");
        Assert.assertFalse(upper.isSorted(),  "The upper witness should have been sorted, but was not");
        Assert.assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper witness but should have");
    }
    
    @Test
    void testTreeSorter() {
        
        Provider generator = new RandomGenerator(10, 100);
        Witness lower = new Witness(generator);
        TreeSorter sorter = new TreeSorter(lower);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(10, lower.getCount());
        Assert.assertEquals(10, upper.getCount());
        Assert.assertFalse(lower.isSorted());  
        Assert.assertTrue(upper.isSorted());  
        Assert.assertEquals(lower.getCrc(), upper.getCrc());
    }

    
    @Test
    void testRandomOrderWithPrinting() {
        
        String test = "testRandomOrderWithPrinting: ";
        
        
        Provider generator = new RandomGenerator(10, 100);
        Printer printer1 = new Printer(generator, test+"from generator");
        Witness lower = new Witness(printer1);
        NoopSorter sorter = new NoopSorter(lower);
        Witness upper = new Witness(sorter);
        Printer printer2 = new Printer(upper, test+"from sorter");
        Consumer consumer = new Consumer(printer2);
        consumer.consume();
        
        Assert.assertEquals(10, lower.getCount());
        Assert.assertEquals(10, upper.getCount());
        Assert.assertFalse(lower.isSorted());  
        Assert.assertFalse(upper.isSorted());  
        Assert.assertEquals(lower.getCrc(), upper.getCrc());
    }

    
    @Test
    void testTreeSorterWithPrinting() {
        
        String test = "testTreeSorterWithPrinting: ";
        
        Provider generator = new RandomGenerator(10, 100);
        Printer printer1 = new Printer(generator, test+"from generator");
        Witness lower = new Witness(printer1);
        TreeSorter sorter = new TreeSorter(lower);
        Witness upper = new Witness(sorter);
        Printer printer2 = new Printer(upper, test+"from sorter");
        Consumer consumer = new Consumer(printer2);
        consumer.consume();
        
        Assert.assertEquals(10, lower.getCount());
        Assert.assertEquals(10, upper.getCount());
        Assert.assertFalse(lower.isSorted());  
        Assert.assertTrue(upper.isSorted());  
        Assert.assertEquals(lower.getCrc(), upper.getCrc());
    }



}
