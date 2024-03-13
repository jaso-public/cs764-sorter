package sorter;

import java.io.File;

public class FileSorter {
    
    private static void usage() {
        System.err.println("usage: FileSorter <recordSize> <input file> <output file>");
        System.exit(1);
    }
    
    public static void main(String[] args) {
        if(args.length != 3) {
            usage();
        }
        
        int recordSize = Integer.parseInt(args[0]);
        
        FileProvider provider = new FileProvider(new File(args[1]), recordSize);
        Sorter sorter = new Sorter(provider, recordSize);
        Witness witness = new Witness(sorter);
        FileConsumer consumer = new FileConsumer(new File(args[2]), witness);
        consumer.consume();
        provider.close();
        consumer.close();
        
        System.out.println(witness);
        
    }
}
