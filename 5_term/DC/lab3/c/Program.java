package lab3.c;

import java.util.Random;

public class Program {
    private static final CyclicBarrier cyclicBarrier = new CyclicBarrier(3, new Dealer());
    private static final BinarySemaphore s = new BinarySemaphore();
    private static final Random rand = new Random();
    private static int missing = 0;

    public enum Supply{
        Paper, Tobacco, Matches
    }

    public static class Smoker implements Runnable{
        private final Supply has;
        private final String name;

        public Smoker(String name, Supply has) {
            super();
            this.has = has;
            this.name = name;
        }

        public void run() {
            while(!Thread.currentThread().isInterrupted()) {
                s.acquire();
                if (has == Supply.values()[missing]) {
                    System.out.printf("%s is smoking...\n", this.name);
                    int sleep = rand.nextInt(4);
                    try {
                        Thread.sleep(sleep * 1000);
                    } catch (InterruptedException e) {
                        return;
                    }
                }
                s.release();

                if(!Thread.currentThread().isInterrupted())
                    cyclicBarrier.await();
            }
        }
    }

    public static class Dealer implements Runnable{
        public void run() {
            missing = rand.nextInt(3);
            System.out.println("Randomizing... " + Supply.values()[missing]+'!');
        }
    }

    public static void main(String[] args) throws InterruptedException  {
        Thread t1 = new Thread(new Smoker("Larry", Supply.Paper));
        Thread t2 = new Thread(new Smoker("Harry", Supply.Tobacco));
        Thread t3 = new Thread(new Smoker("John", Supply.Matches));

        t1.start();
        t2.start();
        t3.start();

        Thread.sleep(10*1000);

        t1.interrupt();
        t2.interrupt();
        t3.interrupt();
    }
}
