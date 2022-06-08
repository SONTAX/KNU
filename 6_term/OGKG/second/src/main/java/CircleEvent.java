public class CircleEvent extends Event {
    public final Arc arc;
    public final Point vertical;

    public CircleEvent(Arc arc, Point point, Point vertical) {
        super(point);
        this.arc = arc;
        this.vertical = vertical;
    }

}