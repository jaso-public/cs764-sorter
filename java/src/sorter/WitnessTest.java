package sorter;



import org.junit.Assert;
import org.junit.jupiter.api.Test;

/**
 * JUnit tests to test that our sorting algorithm is working properly by utilizing the Witness class
 */
class WitnessTest {

    /**
     * Checks that 10 records of size 100 are properly created with the InOrderGenerator
     * Tests that sorting is properly completed with NoopSorter for the upper witness and checksums of lower and upper witness are equal
     */
    @Test
    void testTenInorder() {
        
        Provider generator = new InOrderGenerator(10, 100);
        Witness lower = new Witness(generator);
        NoopSorter sorter = new NoopSorter(lower);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(lower.getCount(), upper.getCount(), "The count of the lower witness did not equal the count of the upper but should have");
        Assert.assertEquals(10, upper.getCount(), "The count of the upper witness was " + upper.getCount() + " but should have been 10");
        Assert.assertTrue(upper.isSorted(), "The upper witness should have been sorted but was not");
        Assert.assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper but should have");
    }

    /**
     * Checks that DropFirst can drop the first record
     * Tests that sorting for both witnesses is properly completed with NoopSorter and lower and upper witness checksum do not equal
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
        
        Assert.assertEquals(10, lower.getCount(),  "The count of the lower witness was " + lower.getCount() + " but should have been 10");
        Assert.assertEquals(9, upper.getCount(), "The count of the upper witness was " + upper.getCount() + " but should have been 9");
        Assert.assertTrue(lower.isSorted(),  "The lower witness should have been sorted, but was not");
        Assert.assertTrue(upper.isSorted(),  "The upper witness should have been sorted, but was not");
        Assert.assertNotEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness equaled the checksum of the upper but should not have");
    }

    /**
     * Checks that 10 records of size 100 are properly created with the RandomGenerator
     * Tests that the lower and upper witness are not sorted but their checksums equal
     */
    @Test
    void testRandomOrder() {
        Provider generator = new RandomGenerator(10, 100);
        Witness lower = new Witness(generator);
        NoopSorter sorter = new NoopSorter(lower);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(10, lower.getCount(),  "The count of the lower witness was " + lower.getCount() + " but should have been 10");
        Assert.assertEquals(10, upper.getCount(),  "The count of the upper witness was " + upper.getCount() + " but should have been 10");
        Assert.assertFalse(lower.isSorted(),  "The lower witness should not have been sorted but was");
        Assert.assertFalse(upper.isSorted(),  "The upper witness should not have been sorted but was");
        Assert.assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper witness but should have");
    }

    /**
     * Checks that 10 records of size 100 are properly created with the RandomGenerator
     * Checks that TreeSorter algorithm properly sorts the upper witness
     */
    @Test
    void testTreeSorter() {
        
        Provider generator = new RandomGenerator(10, 100);
        Witness lower = new Witness(generator);
        TreeSorter sorter = new TreeSorter(lower);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(10, lower.getCount(),  "The count of the lower witness was " + lower.getCount() + " but should have been 10");
        Assert.assertEquals(10, upper.getCount(),  "The count of the upper witness was " + upper.getCount() + " but should have been 10");
        Assert.assertFalse(lower.isSorted(), "The lower witness should not have been sorted but was");
        Assert.assertTrue(upper.isSorted()), "The upper witness should have been sorted but was not";
        Assert.assertEquals(lower.getCrc(), upper.getCrc(),  "The checksum of the lower witness did not equal the checksum of the upper but should have");
    }

    /**
     * This test checks that the given message is printed out to the console using the Printer class using the NoopSorter class for sorting
     */
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
        
        Assert.assertEquals(10, lower.getCount(),  "The count of the lower witness was " + lower.getCount() + " but should have been 10");
        Assert.assertEquals(10, upper.getCount(),  "The count of the upper witness was " + upper.getCount() + " but should have been 10");
        Assert.assertFalse(lower.isSorted(), "The lower witness should not have been sorted but was");
        Assert.assertFalse(upper.isSorted(), "The upper witness should not have been sorted but was");
        Assert.assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper but should have");
    }


    /**
     * This test checks that the given message is printed out to the console using the Printer class using the TreeMap class for sorting
     */
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
        
        Assert.assertEquals(10, lower.getCount(), "The count of the lower witness was " + lower.getCount() + " but should have been 10");
        Assert.assertEquals(10, upper.getCount(), "The count of the upper witness was " + upper.getCount() + " but should have been 10");
        Assert.assertFalse(lower.isSorted(),  "The lower witness should not have been sorted but was");
        Assert.assertTrue(upper.isSorted(), "The upper witness was not sorted but should have been");
        Assert.assertEquals(lower.getCrc(), upper.getCrc(), "The checksum of the lower witness did not equal the checksum of the upper but should have");
    }



}
