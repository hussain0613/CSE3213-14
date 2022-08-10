import java.util.List;

public class Writer implements Runnable{
    private static int _pid = 0;
    
    private int pid;
    Buffer buffer;
    List<Integer> dataList;

    public Writer(){
        this.pid = _pid++;
    }

    public Writer(List<Integer> dataList , Buffer buffer){
        this();
        this.dataList = dataList;
        this.buffer = buffer;
    }

    public void write() throws InterruptedException{
        for(int i = 0; i < dataList.size(); ++i){
            int data = dataList.get(i);
            System.out.println("Writer-" + pid + " writing..." + data);
            buffer.write(data);
            System.out.println("Writer-" + pid + " written: " + data);
            Thread.sleep(100);
        }
        
    }

    public void run(){
        try {
            write();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
