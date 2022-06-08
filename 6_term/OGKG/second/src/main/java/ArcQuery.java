public class ArcQuery extends ArcKey {
    private final Point point;
    public ArcQuery(Point point) {
        this.point = point;
    }

    protected Point getLeft() {
        return point;
    }

    protected Point getRight() {
        return point;
    }
}