import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class Buffer {
    static private final Semaphore mutex = new Semaphore(1);
    static private final Semaphore cap_sem = new Semaphore(1);

    final int MAX_SIZE = 5;
    private Queue<Integer> buffer;
    
    public Buffer(){
        buffer = new LinkedList<Integer>();
    }
    public int read() throws InterruptedException{
        while(buffer.isEmpty()){
            wait();
        }
        mutex.acquire();
        int data = buffer.poll();
        if(buffer.size() == MAX_SIZE - 1) notifyAll();
        mutex.release();
        return data;
    }

    public void write(int data) throws InterruptedException{
        while(buffer.size() > MAX_SIZE){
            wait();
        }
        mutex.acquire();
        buffer.add(data);
        if(buffer.size() == 1) notifyAll();
        mutex.release();
    }
}
