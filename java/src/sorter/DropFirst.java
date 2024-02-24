package sorter;


public class DropFirst implements Provider {

    public final Provider source;
    
    public DropFirst(Provider source) {
        this.source = source;
        source.next(); // drop the first record.
    }
    
    @Override
    public Record next() {
        return source.next();
    }

}
