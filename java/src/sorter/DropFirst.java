package sorter;

/**
 * This class is utilized to automatically obtain the first record
 * The next() method can be called to generate the next record
 */
public class DropFirst implements Provider {

    public final Provider source;
    
    public DropFirst(Provider source) {
        this.source = source;
        source.next(); // drop the first record.
    }

    // returns the next record generated by the provider
    @Override
    public Record next() {
        return source.next();
    }

}
