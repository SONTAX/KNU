package company.plans.exception;

public class NegativeUsersAmount extends RuntimeException {
    public NegativeUsersAmount() {

    }

    public NegativeUsersAmount(String message) {
        super(message);
    }
}
