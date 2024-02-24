package sorter;



import org.junit.Assert;
import org.junit.jupiter.api.Test;

class WitnessTest {

    @Test
    void testTenInorder() {
        
        Provider generator = new InOrderGenerator(10, 100);
        Witness lower = new Witness(generator);
        NoopSorter sorter = new NoopSorter(lower);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(lower.getCount(), upper.getCount());
        Assert.assertEquals(10, upper.getCount());
        Assert.assertTrue(upper.isSorted());  
        Assert.assertEquals(lower.getCrc(), upper.getCrc());
    }

    
    @Test
    void testDropOne() {
        
        Provider generator = new InOrderGenerator(10, 100);
        Witness lower = new Witness(generator);
        DropFirst dropper = new DropFirst(lower);
        NoopSorter sorter = new NoopSorter(dropper);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(10, lower.getCount());
        Assert.assertEquals(9, upper.getCount());
        Assert.assertTrue(lower.isSorted());  
        Assert.assertTrue(upper.isSorted());  
        Assert.assertNotEquals(lower.getCrc(), upper.getCrc());
    }

    @Test
    void testRandomOrder() {
        
        Provider generator = new RandomGenerator(10, 100);
        Witness lower = new Witness(generator);
        NoopSorter sorter = new NoopSorter(lower);
        Witness upper = new Witness(sorter);
        Consumer consumer = new Consumer(upper);
        consumer.consume();
        
        Assert.assertEquals(10, lower.getCount());
        Assert.assertEquals(10, upper.getCount());
        Assert.assertFalse(lower.isSorted());  
        Assert.assertFalse(upper.isSorted());  
        Assert.assertEquals(lower.getCrc(), upper.getCrc());
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
