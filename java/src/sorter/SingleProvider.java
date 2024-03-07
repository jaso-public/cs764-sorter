package sorter;

public class SingleProvider implements Provider {

    private Record rec;
        
    public void reset(Record r) {
        rec = r;
    }

    @Override
    public Record next() {
        Record result = rec;
        rec = null;
        return result;
    }
}
