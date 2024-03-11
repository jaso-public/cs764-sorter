package sorter;


public class NoopSorter implements Provider {

    public final Provider source;
    
    public NoopSorter(Provider source) {
        this.source = source;
    }
    
    @Override
    public Record next() {
        return source.next();
    }

}
