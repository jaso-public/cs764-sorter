package sorter;

/**
 * This class is utilized to receive records using the Provider class
 */
public class Consumer {

    public final Provider source;
    public Consumer(Provider source) {
        this.source = source;
    }

    // Continues to obtain new records until a null record is returned
    void consume() {
        while(true) {
            Record record = source.next();
            if(record == null) return;
        }
    }
}
