package sorter;

public class Printer implements Provider {
    
    public final Provider source;
    public String message;
     
    public Printer(Provider source, String message) {
        this.source = source;
        this.message = message;
    }

    @Override
    public Record next() {
        Record rec = source.next();
        if(rec==null) {
            System.out.println(message+": record is null!");
            return null;
        }
        System.out.println(message+": "+rec.getKey()+" "+Long.toHexString(rec.getCrc()));
        return rec;
    }
    
}
