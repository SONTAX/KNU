package scheduling;

public class sProcess {
  public int id;
  public int executionTime;
  public int period;
  public int deadline;
  public int executedTime = 0;
  public int totalExecutionTime = 0;
  public int totalWaitingTime = 0;
  public int missedDeadlineCounter = 0;
  public int totalCompleteTime = 0;
  public boolean isCurrentlyAvailable = true;

  public sProcess (int executionTime, int period, int deadline, int id) {
    this.executionTime = executionTime;
    this.period = period;
    this.deadline = deadline;
    this.id = id;
    int[] sad = new int[2];
    for (int i = 0; i < sad.length; i++) {

    }
  }
}
