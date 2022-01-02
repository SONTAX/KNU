package company.plans.exception;

public class NegativePrice extends RuntimeException {
    public NegativePrice() {

    }

    public NegativePrice(String message) {
        super(message);
    }
}
