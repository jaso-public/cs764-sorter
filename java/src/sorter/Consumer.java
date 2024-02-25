package sorter;

/**
 * This class is utilized to receive records using the Provider class
 * Continues to obtain new records until a null record is returned
 */
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
