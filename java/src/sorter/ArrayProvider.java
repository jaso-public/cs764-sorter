package sorter;

import java.util.Iterator;

public class ArrayProvider implements Provider {

    @SuppressWarnings("unused")
    private final String name;
    private final Iterator<Record> records;
    
     
    public ArrayProvider(String name, Iterator<Record> records) {
        this.name = name;
        this.records = records;
    }


    @Override
    public Record next() {
        //System.out.println("from "+name);
        if(records.hasNext()) {
            Record result = records.next();
            //System.out.println(name+": key="+result.getKey());
            return result;
        }
        
        //System.out.println(name+": null");
        return null;
    }
}
