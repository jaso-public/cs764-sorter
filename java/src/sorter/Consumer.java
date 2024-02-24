package sorter;

public class Consumer {

    public final Provider source;
    
    public Consumer(Provider source) {
        this.source = source;
    }
    
    void consume() {
        while(true) {
            Record record = source.next();
            if(record == null) return;
        }
    }
}
