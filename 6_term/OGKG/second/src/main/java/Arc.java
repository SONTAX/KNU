public class Arc extends ArcKey {
    private final Voronoi voronoi;
    public BreakPoint left;
    public BreakPoint right;
    public final Point site;

    public Arc(BreakPoint left, BreakPoint right, Voronoi voronoi) {
        this.voronoi = voronoi;
        this.left = left;
        this.right = right;
        this.site = (left != null) ? left.siteRight : right.siteLeft;
    }

    public Arc(Point site, Voronoi voronoi) {
        this.voronoi = voronoi;
        this.left = null;
        this.right = null;
        this.site = site;
    }

    protected Point getRight() {
        if (right != null) {
            return right.getPoint();
        }
        return new Point(Double.POSITIVE_INFINITY, Double.POSITIVE_INFINITY);
    }

    protected Point getLeft() {
        if (this.left != null) {
            return this.left.getPoint();
        }
        return new Point(Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY);
    }

    public Point checkCircle() {
        if ((this.left == null) || (this.right == null)) {
            return null;
        }
        if (Point.counterclockwise(this.left.siteLeft, this.site, this.right.siteRight) != -1) {
            return null;
        }
        return (this.left.getEdge().intersection(this.right.getEdge()));
    }
}