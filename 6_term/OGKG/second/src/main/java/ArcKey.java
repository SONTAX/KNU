public abstract class ArcKey implements Comparable<ArcKey> {
    protected abstract Point getLeft();
    protected abstract Point getRight();

    public int compareTo(ArcKey o) {
        Point thisLeft = this.getLeft();
        Point thisRight = this.getRight();
        Point oLeft = o.getLeft();
        Point oRight = o.getRight();
        if (((o.getClass() == ArcQuery.class) || (this.getClass() == ArcQuery.class)) &&
                ((thisLeft.x <= oLeft.x && thisRight.x >= oRight.x) ||
                        (oLeft.x <= thisLeft.x && oRight.x >= thisRight.x ))) {
            return 0;
        }
        if (thisLeft.x == oLeft.x && thisRight.x == oRight.x) {
            return 0;
        }
        if (thisLeft.x >= oRight.x) {
            return 1;
        }
        if (thisRight.x <= oLeft.x) {
            return -1;
        }
        return Point.midpoint(thisLeft, thisRight).compareTo(Point.midpoint(oLeft, oRight));
    }
}