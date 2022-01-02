package lab1.b;

import javax.swing.*;
import java.util.concurrent.atomic.AtomicInteger;

public class Program {
    private static Thread thread1;
    private static Thread thread2;
    private static AtomicInteger semaphore = new AtomicInteger();

    public static void main(String[] args) {
        JFrame win = new JFrame();
        win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        win.setSize(600, 400);

        JPanel panel = getJPanel();

        win.setContentPane(panel);
        win.setVisible(true);
    }

    private static JPanel getJPanel() {
        JPanel panel = new JPanel();
        JSlider slider = new JSlider();
        JButton bStart1 = new JButton("START 1");
        JButton bStart2 = new JButton("START 2");
        JButton bStop1 = new JButton("STOP 1");
        JButton bStop2 = new JButton("STOP 2");
        bStart1.addActionListener(e -> {
            if (semaphore.compareAndSet(0, 1)) {
                thread1 = new Thread(
                        () -> slider.setValue(10)
                );
                thread1.setPriority(Thread.MIN_PRIORITY);
                thread1.start();
                bStop2.setEnabled(false);
            } else {
                JOptionPane.showMessageDialog(new JFrame(), "Occupied by thread", "Error", JOptionPane.ERROR_MESSAGE);
            }
        });
        bStart2.addActionListener(e -> {
            if (semaphore.compareAndSet(0, 1)) {
                thread2 = new Thread(
                        () -> slider.setValue(90)
                );
                thread2.setPriority(Thread.MAX_PRIORITY);
                thread2.start();
                bStop1.setEnabled(false);
            } else {
                JOptionPane.showMessageDialog(new JFrame(), "Occupied by thread", "Error", JOptionPane.ERROR_MESSAGE);
            }
        });
        bStop1.addActionListener(e -> {
            thread1.stop();
            bStop2.setEnabled(true);
            semaphore.set(0);
        });
        bStop2.addActionListener(e -> {
            thread2.stop();
            bStop1.setEnabled(true);
            semaphore.set(0);
        });
        panel.add(bStart1);
        panel.add(bStop1);
        panel.add(slider);
        panel.add(bStart2);
        panel.add(bStop2);
        return panel;
    }
}

