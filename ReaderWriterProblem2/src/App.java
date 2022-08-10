import java.util.ArrayList;

public class App {
    public static void main(String[] args) throws Exception {
        Buffer buffer = new Buffer();

        int n = 5;

        ArrayList<Thread> threads = new ArrayList<Thread>();

        ArrayList<Writer> writers = new ArrayList<Writer>();
        for(int i = 0; i < n; ++i){
            Writer writer = new Writer(buffer);
            writers.add(writer);

            Thread thread = new Thread(writer);
            threads.add(thread);
        }

        ArrayList<Reader> readers = new ArrayList<Reader>();
        for(int i = 0; i < n; ++i){
            Reader reader = new Reader(buffer);
            readers.add(reader);

            Thread thread = new Thread(reader);
            threads.add(thread);
        }


        for(int i = 0; i < threads.size(); ++i){
            threads.get(i).start();
        }

    }
}
