public class Reader implements Runnable{
    private static int _pid;

    private int pid;
    Buffer buffer;

    public Reader(){
        this.pid = _pid++;
    }

    public Reader(Buffer buffer){
        this();
        this.buffer = buffer;
    }

    public void read() throws InterruptedException{
        
        System.out.println("Reader-" + pid + " reading...");
        int data = buffer.read();
        System.out.println("Reader-" + pid + " read: " + data);
    }

    public void run(){
        try {
            read();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
