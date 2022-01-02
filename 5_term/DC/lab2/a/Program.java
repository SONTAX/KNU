package lab2.a;

import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class Program {
    static AtomicBoolean found = new AtomicBoolean(false);
    static int[][] forest = new int[100][100];
    static Thread Thread1;
    static Thread Thread2;
    static Thread Thread3;
    static Thread Thread4;

    public static void main(String[] args) {
        Random randomGenerator = new Random();
        forest[randomGenerator.nextInt(100)][randomGenerator.nextInt(100)] = 1;
        for (int i = 0; i < 100; i += 4) {
            if (!found.get()) {
                rowsCheck(i);
                System.out.println(i);
            } else {
                return;
            }
        }
    }

    private static void rowsCheck(int row) {
        Thread1 = new Thread(
                () -> {
                    for (int j = 0; j < 100; j++) {
                        if (forest[row][j] == 1) {
                            found.set(true);
                            System.out.println("PUNISHED BY 1 FLOCK in " + (row) + " row");
                            break;
                        }
                    }
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException interruptedException) {
                        interruptedException.printStackTrace();
                    }
                }
        );
        Thread2 = new Thread(
                () -> {
                    for (int j = 0; j < 100; j++) {
                        if (forest[row + 1][j] == 1) {
                            found.set(true);
                            System.out.println("PUNISHED BY 2 FLOCK in " + (row + 1) + " row");
                            break;
                        }
                    }
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException interruptedException) {
                        interruptedException.printStackTrace();
                    }
                }
        );
        Thread3 = new Thread(
                () -> {
                    for (int j = 0; j < 100; j++) {
                        if (forest[row + 2][j] == 1) {
                            found.set(true);
                            System.out.println("PUNISHED BY 3 FLOCK in " + (row + 2) + " row");
                            break;
                        }
                    }
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException interruptedException) {
                        interruptedException.printStackTrace();
                    }
                }
        );
        Thread4 = new Thread(
                () -> {
                    for (int j = 0; j < 100; j++) {
                        if (forest[row + 3][j] == 1) {
                            found.set(true);
                            System.out.println("PUNISHED BY 4 FLOCK in " + (row + 3) + " row");
                            break;
                        }
                    }
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException interruptedException) {
                        interruptedException.printStackTrace();
                    }
                }
        );
        Thread1.start();
        Thread2.start();
        Thread3.start();
        Thread4.start();
    }
}
