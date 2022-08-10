public class Reader implements Runnable{
    static private int _id;

    int id;
    private Buffer buffer;
    
    public Reader(){
        buffer = null;
        this.id = _id++;
    }

    public Reader(Buffer buffer){
        this();
        this.buffer = buffer;
    }

    public void read() throws InterruptedException{
        int data = buffer.read();
        System.out.println(Thread.currentThread().getName() + ": reading " + data);
        Thread.sleep(100);
        System.out.println(Thread.currentThread().getName() + ": leaves.");
    }

    public void run(){
        Thread.currentThread().setName("Reader-"+ id);
        try {
            read();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}