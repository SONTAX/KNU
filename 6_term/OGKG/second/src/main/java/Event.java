public class Event implements Comparable<Event> {
    public final Point point;

    public Event(Point point) {
        this.point = point;
    }

    @Override
    public int compareTo(Event o) {
        return Point.minYOrderedCompareTo(this.point, o.point);
    }
}