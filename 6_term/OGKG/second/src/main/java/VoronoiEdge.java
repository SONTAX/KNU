public class VoronoiEdge {
    public final Point siteLeft;
    public final Point siteRight;
    public final double middle;
    public final double beach;
    public final boolean isVertical;
    public Point pointLeft, pointRight;

    public VoronoiEdge(Point siteLeft, Point siteRight) {
        this.siteLeft = siteLeft;
        this.siteRight = siteRight;
        isVertical = siteLeft.y == siteRight.y;
        if (isVertical) middle = beach = 0;
        else {
            middle = -1.0 / ((siteLeft.y - siteRight.y) / (siteLeft.x - siteRight.x));
            Point midpoint = Point.midpoint(siteLeft, siteRight);
            beach = midpoint.y - middle * midpoint.x;
        }
    }

    public Point intersection(VoronoiEdge edge) {
        if (this.middle == edge.middle && this.beach != edge.beach && this.isVertical == edge.isVertical) {
            return null;
        }
        double x, y;
        if (this.isVertical) {
            x = (this.siteLeft.x + this.siteRight.x) / 2;
            y = edge.middle * x + edge.beach;
        }
        else if (edge.isVertical) {
            x = (edge.siteLeft.x + edge.siteRight.x) / 2;
            y = this.middle *x + this.beach;
        }
        else {
            x = (edge.beach - this.beach) / (this.middle - edge.middle);
            y = middle * x + beach;
        }
        return new Point(x, y);
    }
}