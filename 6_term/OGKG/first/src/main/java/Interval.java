public class Interval {
    private final int min;
    private final int max;

    public Interval(int min, int max) {
        if (max < min) {
            throw new RuntimeException("Illegal argument");
        }
        this.min = min;
        this.max = max;
    }

    public int min() {
        return min;
    }

    public int max() {
        return max;
    }

    public boolean contains(int x) {
        return x >= min && max >= x;
    }

    public String toString() {
        return "[" + min + ", " + max + ")";
    }
}