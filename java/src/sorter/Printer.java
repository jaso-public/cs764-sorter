package sorter;

/**
 * This class is utilized print out the next record with a desired message
 */
public class Printer implements Provider {
    
    public final Provider source;
    // message to be printed out for each record
    public String message;
     
    public Printer(Provider source, String message) {
        this.source = source;
        this.message = message;
    }

    /**
     * Obtains the next record and prints out the record's key and checksum if not null
     * @return the next generated record or null if all records have been generated
     */
    @Override
    public Record next() {
        Record rec = source.next();
        if(rec==null) {
            System.out.println(System.currentTimeMillis()+" "+message+": record is null!");
            return null;
        }
        System.out.println(System.currentTimeMillis()+" "+message+": "+rec.getKey()+" "+Long.toHexString(rec.getCrc()));
        return rec;
    }
    
}
