public class BreakPoint {
    private final Voronoi voronoi;
    protected final Point siteLeft, siteRight;
    private final VoronoiEdge edge;
    private final boolean isEdgeLeft;
    public final Point edgeBegin;
    private double cacheSweepLocation;
    private Point cachePoint;

    public BreakPoint(Point left, Point right, VoronoiEdge edge, boolean isEdgeLeft, Voronoi voronoi) {
        this.voronoi = voronoi;
        this.siteLeft = left;
        this.siteRight = right;
        this.edge = edge;
        this.isEdgeLeft = isEdgeLeft;
        this.edgeBegin = this.getPoint();
    }

    private static double square(double d) {
        return d * d;
    }

    public void finish(Point vert) {
        if (isEdgeLeft) {
            this.edge.pointLeft = vert;
        }
        else {
            this.edge.pointRight = vert;
        }
    }

    public void finish() {
        Point p = this.getPoint();
        if (isEdgeLeft) {
            this.edge.pointLeft = p;
        }
        else {
            this.edge.pointRight = p;
        }
    }

    public Point getPoint() {
        double sweepLocation = voronoi.getSweepLocation();
        if (sweepLocation == cacheSweepLocation) {
            return cachePoint;
        }
        cacheSweepLocation = sweepLocation;
        double x,y;
        if (siteLeft.y == siteRight.y) {
            x = (siteLeft.x + siteRight.x) / 2;
            y = (square(x - siteLeft.x) + square(siteLeft.y) - square(sweepLocation)) / (2 * (siteLeft.y - sweepLocation));
        }
        else {
            double px = (siteLeft.y > siteRight.y) ? siteLeft.x : siteRight.x;
            double py = (siteLeft.y > siteRight.y) ? siteLeft.y : siteRight.y;
            double middle = edge.middle;
            double beach = edge.beach;
            double distance = 2 * (py - sweepLocation);
            double A = 1;
            double B = -2 * px - distance * middle;
            double C = square(px) + square(py) - square(sweepLocation) - distance * beach;
            int sign = (siteLeft.y > siteRight.y) ? -1 : 1;
            double det = square(B) - 4 * A * C;
            if (det <= 0) {
                x = -B / (2 * A);
            }
            else {
                x = (-B + sign * Math.sqrt(det)) / (2 * A);
            }
            y = middle * x + beach;
        }
        cachePoint = new Point(x, y);
        return cachePoint;
    }

    public VoronoiEdge getEdge() {
        return this.edge;
    }
}