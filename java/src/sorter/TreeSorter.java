package sorter;

import java.util.Iterator;
import java.util.TreeMap;

public class TreeSorter implements Provider{
  
    private Iterator<Record> records;
    
    static class Key implements Comparable<Key>{
        private final long key;
        private final long index;

        public Key(long key, long index) {
            this.key = key;
            this.index = index;
        }
        
        @Override
        public int compareTo(Key other) {
            if(this.key < other.key) return -1;
            if(this.key > other.key) return +1;
            if(this.index < other.index) return -1;
            if(this.index > other.index) return +1;
            return 0;
        }
    }
    
    public TreeSorter(Provider source) {
        long index = 0;
        TreeMap<Key,Record> sorted = new TreeMap<>();
        while(true) {
            Record record = source.next();
            if(record == null) break;
            sorted.put(new Key(record.getKey(), index++), record);
        }
        records = sorted.values().iterator();
    }
    
    @Override
    public Record next() {
        if(records.hasNext()) return records.next();
        return null;
    }

}
