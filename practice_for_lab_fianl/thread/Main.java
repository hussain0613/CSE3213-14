package practice_for_lab_fianl.thread;

import java.util.concurrent.Semaphore;

class SharedNumber{
    private double n;
    private Semaphore mutex = new Semaphore(1);

    public SharedNumber(double n){
        this.n = n;
    }
    public double getN(){
        return n;
    }
    public void add(int m) throws InterruptedException{
        mutex.acquire();
        Thread.sleep(2); // to visibly see the difference between doing it with and without mutex
        n += m;
        mutex.release();
    }
}

class CalculateSum extends Thread{
    private SharedNumber sn;
    private int start, end;
    CalculateSum(SharedNumber sn, int start, int end){
        this.sn = sn;
        this.start = start;
        this.end = end;
    }
    public void run(){
        for(int i = start; i <= end; ++i){
            // System.out.println(Thread.currentThread().getName());
            try {
                sn.add(i);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }
}

public class Main {
    public static void main(String[] args){
        SharedNumber sn = new SharedNumber(0.0);
        CalculateSum cs1 = new CalculateSum(sn, 1, 500), cs2 = new CalculateSum(sn, 501, 1000);

        cs1.start();
        cs2.start();

        while(cs1.isAlive() || cs2.isAlive());
        System.out.println("Final output: " + sn.getN());
    }
    
}
