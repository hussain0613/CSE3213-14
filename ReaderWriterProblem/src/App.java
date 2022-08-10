import java.util.ArrayList;

public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");

        ArrayList<Integer> dataList = new ArrayList<Integer>();
        dataList.add(25);
        dataList.add(57);
        dataList.add(60);
        dataList.add(13);
        dataList.add(97);

        Buffer buffer = new Buffer();

        Writer writer1 = new Writer(dataList, buffer);
        Writer writer2 = new Writer(dataList, buffer);

        Reader reader1 = new Reader(buffer);
        Reader reader2 = new Reader(buffer);

        Thread t1 = new Thread(writer1, "w1"), t2 = new Thread(writer2, "w2"), t3 = new Thread(reader1, "r1"), t4 = new Thread(reader2, "r2");

        t1.start();
        t2.start();
        t3.start();
        t4.start();
    }
}
