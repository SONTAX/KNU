public class Interval2D {
    public final Interval intervalX;
    public final Interval intervalY;

    public Interval2D(Interval intervalX, Interval intervalY) {
        this.intervalX = intervalX;
        this.intervalY = intervalY;
    }

    public String toString() {
        return intervalX + " x " + intervalY;
    }
}