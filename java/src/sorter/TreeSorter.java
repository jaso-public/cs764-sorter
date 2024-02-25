package sorter;

import java.util.Iterator;
import java.util.TreeMap;

/**
 * This class is used retrieve a sorted TreeMap of records and compare record's key/indexes within the TreeMap
 */

public class TreeSorter implements Provider{

    // stores all records in sorted order
    private Iterator<Record> records;
    
    static class Key implements Comparable<Key>{
        // key of the record
        private final long key;
        // record's index in Iterator
        private final long index;

        public Key(long key, long index) {
            this.key = key;
            this.index = index;
        }

        /**
         * This method is utilized to compare a record to another record based on its key or index
         * @param other the other Key to compare to the current Key
         * @return -1 if current key/index is less than other key/index or 1 if current key/index is greater than other key/index
         */
        @Override
        public int compareTo(Key other) {
            if(this.key < other.key) return -1;
            if(this.key > other.key) return +1;
            // if key's are the same, then compares indexes
            if(this.index < other.index) return -1;
            if(this.index > other.index) return +1;
            return 0;
        }
    }

    /**
     * Creates a tree map of records in sorted order that can be iterated through
     * @param source the Provider to create the records
     */
    public TreeSorter(Provider source) {
        long index = 0;
        TreeMap<Key,Record> sorted = new TreeMap<>();
        // adds all record to TreeMap until count has been reached
        while(true) {
            Record record = source.next();
            if(record == null) break;
            sorted.put(new Key(record.getKey(), index++), record);
        }
        records = sorted.values().iterator();
    }

    /**
     * Returns the next sorted record or null if no other records are in list
     * @return next record or null
     */
    @Override
    public Record next() {
        if(records.hasNext()) return records.next();
        return null;
    }

}
