import java.awt.*;

public class Point implements Comparable<Point> {
    public final double x;
    public final double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public int compareTo(Point o) {
        if ((this.x == o.x) || (Double.isNaN(this.x) && Double.isNaN(o.x))) {
            if (this.y == o.y) {
                return 0;
            }
            return (this.y < o.y) ? -1 : 1;
        }
        return (this.x < o.x) ? -1 : 1;
    }

    public static int minYOrderedCompareTo(Point point1, Point point2) {
        if (point1.y < point2.y) return 1;
        if (point1.y > point2.y) return -1;
        if (point1.x == point2.x) return 0;
        return (point1.x < point2.x) ? -1 : 1;
    }

    public static Point midpoint(Point point1, Point point2) {
        double x = (point1.x + point2.x) / 2;
        double y = (point1.y + point2.y) / 2;
        return new Point(x, y);
    }

    public static int counterclockwise(Point a, Point b, Point c) {
        double area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        if      (area < 0) return -1;
        else if (area > 0) return +1;
        else                return  0;
    }

    public double distanceTo(Point point) {
        return Math.sqrt((this.x - point.x) * (this.x - point.x) + (this.y - point.y) * (this.y - point.y));
    }

    public void draw(Color c) {
        Color old = StdDraw.getPenColor();
        StdDraw.setPenColor(c);
        StdDraw.setPenRadius(.01);
        StdDraw.point(x, y);
        StdDraw.setPenRadius();
        StdDraw.setPenColor(old);
    }

    private static boolean equals(double a, double b) {
        if (a == b)
            return true;
        double EPSILON = 0.0000001;
        return Math.abs(a - b) < EPSILON * Math.max(Math.abs(a), Math.abs(b));
    }

    @Override
    public boolean equals(Object o) {
        return o instanceof Point && equals(((Point) o).x, this.x) && equals(((Point) o).y, this.y);
    }
}