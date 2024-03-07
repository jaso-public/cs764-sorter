package sorter;

public class sim {

    public static void main(String[] args) {
        float percentage = 0.01F;
        
        int numToSort = 120 * 1024;
        int sorted = 0;
        int freeBlocks = 99;
        
        int ssdFree = 10 * 1024;
        
        int ssdStreams = 0;
        int ssdSize = 0;
        
        int hddStreams = 0;
        int hddSize = 0;
        
        while(sorted < numToSort) {
            sorted += freeBlocks;
            freeBlocks = 0;
            
            int numToMove = (int)(sorted * percentage); 
            //System.out.println("numToMove:"+numToMove);
            if(numToMove < 1) numToMove = 1;
            if(numToMove > 99) numToMove = 99;
            if(ssdFree > 0) {
                if(numToMove > ssdFree) numToMove = ssdFree;
                ssdFree -= numToMove;
                ssdStreams++;
                System.out.println("ssd: "+ssdStreams+" "+numToMove+" "+ssdSize);
            } else {                
                hddSize += numToMove;
                hddStreams++;
                System.out.println("hdd: "+hddStreams+" "+numToMove+" "+hddSize);
            }
            
            freeBlocks += numToMove;
        }
        
        System.out.println("ssdStreams:"+ssdStreams);
        System.out.println("hddStreams:"+hddStreams);
        System.out.println("hddSize:"+hddSize);
        
        double total = ssdStreams + hddStreams;
        total /= 16;
        System.out.println("total: "+total);
        
    }

}
