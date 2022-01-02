package lab2.b;

import java.util.Random;

public class Program {
    public static void main(String[] args) {
        Controller controller = new Controller();
        new Controller.Ivanov(controller);
        new Controller.Petrov(controller);
        new Controller.Nechiporchuk(controller);
        System.out.println("Start");
    }
}

class Controller {
    static final Random randomGenerator = new Random();
    static int totalStilled = 0;
    int firstBuffer;
    int secondBuffer;
    boolean isFirstBufferEmpty = true;
    boolean isSecondBufferEmpty = true;

    synchronized int getFromFirst() {
        while (isFirstBufferEmpty) {
            try {
                wait();
            } catch (InterruptedException interruptedException) {
                interruptedException.printStackTrace();
            }
        }
        System.out.println("Get1: " + firstBuffer);
        isFirstBufferEmpty = true;
        notifyAll();
        return firstBuffer;
    }

    synchronized int getFromSecond() {
        while (isSecondBufferEmpty)
            try {
                wait();
            } catch (InterruptedException interruptedException) {
                interruptedException.printStackTrace();
            }
        System.out.println("Get2: " + secondBuffer);
        isSecondBufferEmpty = true;
        notifyAll();
        return secondBuffer;
    }

    synchronized void putToFirst(int n) {
        while (!isFirstBufferEmpty) {
            try {
                wait();
            } catch (InterruptedException interruptedException) {
                interruptedException.printStackTrace();
            }
        }
        this.firstBuffer = n;
        System.out.println("Set1: " + n);
        isFirstBufferEmpty = false;
        notifyAll();
    }

    synchronized void putToSecond(int n) {
        while (!isSecondBufferEmpty) {
            try {
                wait();
            } catch (InterruptedException interruptedException) {
                interruptedException.printStackTrace();
            }
        }
        this.secondBuffer = n;
        System.out.println("Set2: " + n);
        isSecondBufferEmpty = false;
        notifyAll();
    }

    public static class Ivanov implements Runnable {
        Controller controller;

        Ivanov(Controller controller) {
            this.controller = controller;
            new Thread(this).start();
        }

        @Override
        public void run() {
            while (true) {
                controller.putToFirst(randomGenerator.nextInt(100));
            }
        }
    }

    public static class Petrov implements Runnable {
        Controller controller;

        Petrov(Controller controller) {
            this.controller = controller;
            new Thread(this).start();
        }

        @Override
        public void run() {
            while (true) {
                int thing = controller.getFromFirst();
                controller.putToSecond(thing);
            }
        }
    }

    public static class Nechiporchuk implements Runnable {
        Controller controller;

        Nechiporchuk(Controller controller) {
            this.controller = controller;
            new Thread(this).start();
        }

        @Override
        public void run() {
            while (true) {
                totalStilled += controller.getFromSecond();
            }
        }
    }
}