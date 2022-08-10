import java.util.Queue;

public class Buffer {
    private Queue<String> buffer;
    private int size = 5;

    synchronized public String read() throws InterruptedException{ // consumer will read
        if(buffer.size() <= 0) wait();
        
        return buffer.poll();
    }
    synchronized public void write(String data) throws InterruptedException{ // producer will write
        if(buffer.size() >= size) wait();

        buffer.add(data);
    }
}
