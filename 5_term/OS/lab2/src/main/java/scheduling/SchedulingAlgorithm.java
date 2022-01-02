// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.
package scheduling;

import java.util.Vector;
import java.io.*;

public class SchedulingAlgorithm {

  private static Vector<sProcess> updateAvailability(Vector<sProcess> processVector, int index) {
    Vector<sProcess> updatedProcessVector = new Vector<>(0);
    for (sProcess elem : processVector) {
      if ((index % elem.period == 0) && (index != 0) && !elem.isCurrentlyAvailable) {
        elem.totalExecutionTime += elem.executedTime;
        elem.isCurrentlyAvailable = true;
        elem.executedTime = 0;
        elem.deadline += elem.period;
      }
      updatedProcessVector.add(elem);
    }
    return updatedProcessVector;
  }

  private static int getCurrentProcess(Vector<sProcess> availableProcess) {
    int currentProcess = -1;
    int minDeadline = 2147483647;
    for (int i = 0; i < availableProcess.size(); i++) {
      if ((availableProcess.elementAt(i).deadline < minDeadline) && (availableProcess.elementAt(i).isCurrentlyAvailable)) {
        currentProcess = i;
        minDeadline = availableProcess.elementAt(i).deadline;
      }
    }
    return currentProcess;
  }

  public static void run (int runtime, Vector<sProcess> processVector, Results result, String[][] diagram) {
    int compTime = 0;
    int currentProcess;
    String resultsFile = "Summary-Processes";

    result.schedulingType = "Batch (preemptive)";
    result.schedulingName = "Earliest deadline first";
    try {
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      while (compTime < runtime) {
        out.println("Iteration number: " + compTime);
        processVector = updateAvailability(processVector, compTime);
        currentProcess = getCurrentProcess(processVector);
        if (currentProcess == -1) {
          out.println("There are no available process...");
        } else {
          if (processVector.get(currentProcess).executedTime == 0) {
            out.println("Process: " + processVector.get(currentProcess).id + " registered... (" + processVector.get(currentProcess).executionTime + " " + processVector.get(currentProcess).deadline + " " + processVector.get(currentProcess).period + ")");
          } else {
            out.println("Process: " + processVector.get(currentProcess).id + " continues computing... (" + processVector.get(currentProcess).executedTime + " " + processVector.get(currentProcess).deadline + " " + processVector.get(currentProcess).period + ")");
          }
          processVector.get(currentProcess).executedTime++;
          diagram[currentProcess][compTime] = "#";
          if (processVector.get(currentProcess).executionTime == processVector.get(currentProcess).executedTime) {
            out.println("Process: " + processVector.get(currentProcess).id + " completed... (" + processVector.get(currentProcess).executionTime + " " + processVector.get(currentProcess).deadline + " " + processVector.get(currentProcess).period + ")");
            processVector.get(currentProcess).isCurrentlyAvailable = false;
            processVector.get(currentProcess).totalCompleteTime = compTime;
            processVector.get(currentProcess).totalWaitingTime += compTime + 1 - processVector.get(currentProcess).executionTime - (processVector.get(currentProcess).deadline - processVector.get(currentProcess).period);
            if (processVector.get(currentProcess).deadline < compTime) {
              processVector.get(currentProcess).missedDeadlineCounter++;
            }
          }
        }
        compTime++;
      }
      out.close();
    } catch (IOException ignore) { /* Handle exceptions */ }
    result.compuTime = compTime;
  }
}
