package lab1.a;

import javax.swing.*;

public class Program {
    static Thread thread1;
    static Thread thread2;

    public static void main(String[] args) {
        JFrame win = new JFrame();
        win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        win.setSize(500, 400);

        JPanel panel = getJPanel();

        win.setContentPane(panel);
        win.setVisible(true);
    }

    private static JPanel getJPanel() {
        JPanel panel = new JPanel();
        JSlider slider = new JSlider();
        JButton bStart = new JButton("START");
        JButton bPlus1 = new JButton("+");
        JButton bMinus1 = new JButton("-");
        JButton bPlus2 = new JButton("+");
        JButton bMinus2 = new JButton("-");
        bStart.addActionListener(e -> {

                thread1 = new Thread(
                        () -> {
                            while (slider.getValue() > 10) {
                                synchronized (slider) {
                                    slider.setValue(slider.getValue() - 1);
                                    try {
                                        Thread.sleep(10);
                                    } catch (InterruptedException interruptedException) {
                                        interruptedException.printStackTrace();
                                    }
                                }
                            }
                        }
                );
                thread2 = new Thread(
                        () -> {
                            while (slider.getValue() < 90) {
                                synchronized (slider) {
                                    slider.setValue(slider.getValue() + 1);
                                    try {
                                        Thread.sleep(10);
                                    } catch (InterruptedException interruptedException) {
                                        interruptedException.printStackTrace();
                                    }
                                }
                            }
                        }
                );
            thread1.setPriority(Thread.NORM_PRIORITY);
            thread2.setPriority(Thread.NORM_PRIORITY);
            thread1.setDaemon(true);
            thread2.setDaemon(true);
            thread1.start();
            thread2.start();

        });
        bPlus1.addActionListener(e -> thread1.setPriority(thread1.getPriority() + 1));
        bMinus1.addActionListener(e -> thread1.setPriority(thread1.getPriority() - 1));
        bPlus2.addActionListener(e -> thread2.setPriority(thread2.getPriority() + 1));
        bMinus2.addActionListener(e -> thread2.setPriority(thread2.getPriority() - 1));
        panel.add(bPlus1);
        panel.add(bMinus1);
        panel.add(slider);
        panel.add(bStart);
        panel.add(bPlus2);
        panel.add(bMinus2);
        return panel;
    }
}
