import java.util.ArrayList;
import java.util.concurrent.Semaphore;

public class Buffer {
    int reader_count = 0;
    ArrayList<Integer> buffer;

    Semaphore reader_count_lock = new Semaphore(1);
    Semaphore buffer_lock = new Semaphore(1);
    Semaphore read_lock = new Semaphore(0);

    public Buffer(){
        this.buffer = new ArrayList<Integer>();
    }

    public int read() throws InterruptedException{
        read_lock.acquire();
        

        reader_count_lock.acquire();
        ++reader_count;
        if(reader_count == 1) buffer_lock.acquire();
        reader_count_lock.release();
        
        
        int i = (int)(Math.random() * buffer.size()) % buffer.size();
        int data = buffer.get(i);
        System.out.println(Thread.currentThread().getName() + ": reading " + data);
        
        reader_count_lock.acquire();
        --reader_count;
        if(reader_count == 0) buffer_lock.release();
        reader_count_lock.release();

        return data;
    }

    public void write() throws InterruptedException{
        buffer_lock.acquire();

        int data = (int)(Math.random() * 500);
        buffer.add(data);
        
        System.out.println(Thread.currentThread().getName() + ": writes in the system " + data);

        System.out.print("Data in Buffer: ");
        for(int i = 0; i < buffer.size(); ++i){
            System.out.print(buffer.get(i) + " ");
        }
        System.out.println();
        read_lock.release();
        buffer_lock.release();

        Thread.sleep(100);
        System.out.println(Thread.currentThread().getName() + ": leaves the system");
    }
}
