public class Writer implements Runnable{
    static private int _id;

    int id;
    private Buffer buffer;
    
    public Writer(){
        buffer = null;
        this.id = _id++;
    }

    public Writer(Buffer buffer){
        this();
        this.buffer = buffer;
    }

    public void write() throws InterruptedException{
        buffer.write();
        
    }

    public void run(){
        Thread.currentThread().setName("Writer-"+ id);
        try {
            write();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}