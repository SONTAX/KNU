package lab3.a;

import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

public class Program {
    public static final int N = 50;

    private static Integer honeyPot = 0;
    private static final Semaphore semaphore = new Semaphore(1);
    private static final CyclicBarrier cyclicBarrier = new CyclicBarrier(N, new WinnieThePooh());

    public static class Bee implements Runnable{
        public void run() {
            while(!Thread.currentThread().isInterrupted()) {
                try {
                    semaphore.acquire();
                    ++honeyPot;
                    semaphore.release();
                    Random rand = new Random();
                    float writeMessage = rand.nextFloat();
                    if (writeMessage < 0.15)
                        System.out.println("Bzzzzzzz! Bees are working");
                    cyclicBarrier.await();
                } catch (InterruptedException | BrokenBarrierException e) {
                    return;
                }
            }
        }
    }

    public static class WinnieThePooh implements Runnable {
        public void run() {
            try {
                semaphore.acquire();
                System.out.printf("Pooh eats Honey = %d\n", honeyPot);
                honeyPot = 0;
                semaphore.release();
            } catch (InterruptedException e) {
                return;
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread[] bees = new Thread[N];
        for(int i =0; i < N; ++i) {
            bees[i] = new Thread(new Bee());
            bees[i].start();
        }
        Thread.sleep(100);
        for(Thread t: bees) {
            t.interrupt();
        }
    }
}
