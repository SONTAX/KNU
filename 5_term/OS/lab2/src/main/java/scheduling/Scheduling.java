// This file contains the main() function for the Scheduling
// simulation.  Init() initializes most of the variables by
// reading from a provided file.  SchedulingAlgorithm.Run() is
// called from main() to run the simulation.  Summary-Results
// is where the summary results are written, and Summary-Processes
// is where the process scheduling summary is written.

// Created by Alexander Reeder, 2001 January 06

package scheduling;

import java.io.*;
import java.util.*;

public class Scheduling {

  private static int runtime = 1000;
  private static final Vector<sProcess> processVector = new Vector<>();
  private static final Results result = new Results("null","null",0);
  private static String[][] diagram = new String[0][0];

  private static void Init(String file) {
    File f = new File(file);
    String line;
    Vector<Integer> periods = new Vector<>(0);
    try {
      DataInputStream in = new DataInputStream(new FileInputStream(f));
      while ((line = in.readLine()) != null) {
        if (line.startsWith("process")) {
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();
          int executionTime = Common.s2i(st.nextToken(" "));
          int period = Common.s2i(st.nextToken(" "));
          int deadline = Common.s2i(st.nextToken(" "));
          int id = Common.s2i(st.nextToken(" "));
          processVector.add(new sProcess(executionTime, period, deadline, id));
          periods.add(period);
        }
      }
      in.close();
    } catch (IOException e) { /* Handle exceptions */ }
    runtime = lcm(periods);
    diagram = new String[processVector.size()][runtime];
    for (int i = 0; i < processVector.size(); i++) {
      for (int j =0; j < runtime; j++) {
        diagram[i][j] = " ";
      }
    }
  }

  private static int lcm(Vector<Integer> numbers) {
    int result = numbers.get(0);
    for (int i = 1; i < numbers.size(); i++) {
      result = (numbers.get(i) * result) / gcd(numbers.get(i), result);
    }
    return result;
  }

  private static int gcd(int a, int b) {
    return a == 0 ? b : gcd(b % a, a);
  }

  private static void debug() {
    int size = processVector.size();
    for (int i = 0; i < size; i++) {
      sProcess process = processVector.elementAt(i);
      System.out.println("process " + i + " " + process.executionTime + " " + process.period + " " + process.deadline + " " + process.executedTime);
    }
    System.out.println("runtime " + runtime);
  }

  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Usage: 'java Scheduling <INIT FILE>'");
      System.exit(-1);
    }
    File f = new File(args[0]);
    if (!(f.exists())) {
      System.out.println("Scheduling: error, file '" + f.getName() + "' does not exist.");
      System.exit(-1);
    }  
    if (!(f.canRead())) {
      System.out.println("Scheduling: error, read of " + f.getName() + " failed.");
      System.exit(-1);
    }
    System.out.println("Working...");
    Init(args[0]);
    SchedulingAlgorithm.run(runtime, processVector, result, diagram);
    try {
      String resultsFile = "Summary-Results";
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      out.println("Scheduling Type: " + result.schedulingType);
      out.println("Scheduling Name: " + result.schedulingName);
      out.println("Simulation Run Time: " + result.compuTime);
      out.println("Process #\tPeriod\tExecution time\tDeadline missed times\tTotal complete time\tTotal waiting time");
      for (int i = 0; i < processVector.size(); i++) {
        sProcess process = processVector.elementAt(i);
        out.print(process.id + "\t\t\t" + process.period + "\t\t" + process.executionTime + "\t\t\t\t" + process.missedDeadlineCounter + "\t\t\t\t\t\t" + process.totalCompleteTime + "\t\t\t\t\t" + process.totalWaitingTime + "\n");
      }
      out.println();
      out.print("\t");
      for (int i = 0; i < runtime; i++) {
        out.print(i + "\t");
      }
      for (int i = 0; i < processVector.size(); i++) {
        out.print("\n" + (i + 1) + "\t");
        for (int j = 0; j < runtime; j++) {
          out.print(diagram[i][j] + "\t");
        }
      }
      out.println();
      out.close();
    } catch (IOException ignore) { /* Handle exceptions */ }
    System.out.println("Completed.");
  }
}
