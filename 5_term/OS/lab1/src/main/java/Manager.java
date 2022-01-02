import org.newsclub.net.unix.AFUNIXSocket;
import org.newsclub.net.unix.AFUNIXSocketAddress;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.*;
import java.net.SocketException;
import java.util.Scanner;
import java.util.concurrent.*;

public class Manager implements KeyListener {
    private static ExecutorService executor;
    public static void main(String[] args) throws IOException {
        while (true) {
            execute(Double.parseDouble(args[0]));
            ScheduledExecutorService executorService = Executors.newScheduledThreadPool(1);
            executorService.scheduleWithFixedDelay(() -> {
                Scanner in = new Scanner(System.in);
                System.out.println("Would you like to continue?\n" +
                        "a - continue, b - continue without prompt, c - cancel");
                String ans = in.nextLine();
                if (ans.equals("a")) {
                    try {
                        restart(Double.parseDouble(args[0]));
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                } else if (ans.equals("b")) {
                    executorService.shutdown();
                } else {
                    System.out.println("Computation was canceled");
                    executor.shutdown();
                    Runtime.getRuntime().exit(1);
                }

            }, 5, 5, TimeUnit.SECONDS);


        }
    }

    private static void execute(double x) throws IOException {
        executor = Executors.newFixedThreadPool(2);
        executor.execute(new FunctionComputation('F'));
        executor.execute(new FunctionComputation('G'));
        try (AFUNIXSocket socketF = AFUNIXSocket.newInstance();
             AFUNIXSocket socketG = AFUNIXSocket.newInstance();) {
            try {
                socketF.connect(AFUNIXSocketAddress.of(new File("socketF.socket")));
            } catch (SocketException e) {
                System.out.println("Cannot connect to server for f function");
            }
            try {
                socketG.connect(AFUNIXSocketAddress.of(new File("socketG.socket")));
            } catch (SocketException e) {
                System.out.println("Cannot connect to server for g function");
            }
            System.out.println("Servers are connected");
            try (InputStream inputStreamF = socketF.getInputStream();
                InputStream inputStreamG = socketG.getInputStream();
                 OutputStream outputStreamF = socketF.getOutputStream();
                 OutputStream outputStreamG = socketG.getOutputStream();) {
                DataInputStream dataInputStreamF = new DataInputStream(inputStreamF);
                DataInputStream dataInputStreamG = new DataInputStream(inputStreamG);
                DataOutputStream dataOutputStreamF = new DataOutputStream(outputStreamF);
                DataOutputStream dataOutputStreamG = new DataOutputStream(outputStreamG);
                dataOutputStreamF.writeDouble(x);
                dataOutputStreamG.writeDouble(x);
                dataOutputStreamF.flush();
                dataOutputStreamG.flush();
                double resultF = dataInputStreamF.readDouble();
                double resultG = dataInputStreamG.readDouble();
                System.out.println("f: " + resultF);
                System.out.println("g: " + resultG);
                System.out.println("f | g: " + binaryOperation(resultF, resultG));
            }
        }
        System.out.println("Disconnecting servers...");
        executor.shutdown();
        System.out.println("Disconnected");
    }

    private static void restart(double x) throws IOException {
        executor.shutdown();
        execute(x);
    }

    private static int binaryOperation(double f, double g) {
        return (int)f | (int)g;
    }

    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override
    public void keyPressed(KeyEvent e) {
        if (e.getKeyCode() == KeyEvent.VK_ESCAPE) {
            Scanner in = new Scanner(System.in);
            System.out.print("Please confirm computation cancellation: ");
            if (in.next().equals("y")) {
                System.out.println("Computation was canceled");
                executor.shutdown();
            }
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}
