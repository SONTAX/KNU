import java.util.*;
import java.util.Map.Entry;

public class Voronoi {
    private static final double MAX_DIM = 10;
    private static final double MIN_DIM = -10;
    private double sweepLocation;
    private final ArrayList<Point> sites;
    private final ArrayList<VoronoiEdge> edgeList;
    private final HashSet<BreakPoint> breakPoints;
    private final TreeMap<ArcKey, CircleEvent> arcs;
    private final TreeSet<Event> events;

    public double getSweepLocation() {
        return sweepLocation;
    }

    public static void main(String[] args) {
        int N = 30;
        ArrayList<Point> sites = new ArrayList<>();
        Random rnd = new Random();
        for (int i = 0; i < N; i++) {
            sites.add(new Point(rnd.nextDouble(), rnd.nextDouble()));
        }
        StdDraw.setCanvasSize(512, 512);
        StdDraw.setScale(-0.1, 1.1);
        Voronoi v = new Voronoi(sites);
        v.show();
    }

    public Voronoi(ArrayList<Point> sites) {
        this.sites = sites;
        this.edgeList = new ArrayList<>(sites.size());
        this.events = new TreeSet<>();
        this.breakPoints = new HashSet<>();
        this.arcs = new TreeMap<>();
        for (Point site : sites) {
            events.add(new Event(site));
        }
        this.sweepLocation = MAX_DIM;
        do {
            Event currentEvent = events.pollFirst();
            sweepLocation = currentEvent.point.y;
            if (currentEvent.getClass() == Event.class) {
                handleSiteEvent(currentEvent);
            }
            else {
                CircleEvent circleEvent = (CircleEvent) currentEvent;
                handleCircleEvent(circleEvent);
            }
        } while ((events.size() > 0));
        this.sweepLocation = MIN_DIM;
        for (BreakPoint breakPoint : breakPoints) {
            breakPoint.finish();
        }
    }

    private void handleSiteEvent(Event event) {
        if (arcs.size() == 0) {
            arcs.put(new Arc(event.point, this), null);
            return;
        }
        Map.Entry<ArcKey, CircleEvent> arcEntryAbove = arcs.floorEntry(new ArcQuery(event.point));
        Arc arcAbove = (Arc) arcEntryAbove.getKey();
        CircleEvent toDelete = arcEntryAbove.getValue();
        if (toDelete != null) {
            events.remove(toDelete);
        }
        BreakPoint leftBreakPoint = arcAbove.left;
        BreakPoint rightBreakPoint = arcAbove.right;
        VoronoiEdge newEdge = new VoronoiEdge(arcAbove.site, event.point);
        this.edgeList.add(newEdge);
        BreakPoint newLeftBreakPoint = new BreakPoint(arcAbove.site, event.point, newEdge, true, this);
        BreakPoint newRightBreakPoint = new BreakPoint(event.point, arcAbove.site, newEdge, false, this);
        breakPoints.add(newLeftBreakPoint);
        breakPoints.add(newRightBreakPoint);
        Arc arcLeft = new Arc(leftBreakPoint, newLeftBreakPoint, this);
        Arc center = new Arc(newLeftBreakPoint, newRightBreakPoint, this);
        Arc arcRight = new Arc(newRightBreakPoint, rightBreakPoint, this);
        arcs.remove(arcAbove);
        arcs.put(arcLeft, null);
        arcs.put(center, null);
        arcs.put(arcRight, null);
        checkForCircleEvent(arcLeft);
        checkForCircleEvent(arcRight);
    }

    private void handleCircleEvent(CircleEvent circleEvent) {
        arcs.remove(circleEvent.arc);
        circleEvent.arc.left.finish(circleEvent.vertical);
        circleEvent.arc.right.finish(circleEvent.vertical);
        breakPoints.remove(circleEvent.arc.left);
        breakPoints.remove(circleEvent.arc.right);
        Entry<ArcKey, CircleEvent> entryRight = arcs.higherEntry(circleEvent.arc);
        Entry<ArcKey, CircleEvent> entryLeft = arcs.lowerEntry(circleEvent.arc);
        Arc arcRight = null;
        Arc arcLeft = null;
        if (entryRight != null) {
            arcRight = (Arc) entryRight.getKey();
            CircleEvent toDelete = entryRight.getValue();
            if (toDelete != null) {
                events.remove(toDelete);
                arcs.put(arcRight, null);
            }
        }
        if (entryLeft != null) {
            arcLeft = (Arc) entryLeft.getKey();
            CircleEvent toDelete = entryLeft.getValue();
            if (toDelete != null) {
                events.remove(toDelete);
                arcs.put(arcLeft, null);
            }
        }
        VoronoiEdge edge = new VoronoiEdge(arcLeft.right.siteLeft, arcRight.left.siteRight);
        edgeList.add(edge);
        boolean turnsLeft = Point.counterclockwise(arcLeft.right.edgeBegin, circleEvent.point, arcRight.left.edgeBegin) == 1;
        boolean isLeftPoint = (turnsLeft) ? (edge.middle < 0) : (edge.middle > 0);
        if (isLeftPoint) {
            edge.pointLeft = circleEvent.vertical;
        } else {
            edge.pointRight = circleEvent.vertical;
        }
        BreakPoint newBreakPoint = new BreakPoint(arcLeft.right.siteLeft, arcRight.left.siteRight, edge, !isLeftPoint, this);
        breakPoints.add(newBreakPoint);
        arcRight.left = newBreakPoint;
        arcLeft.right = newBreakPoint;
        checkForCircleEvent(arcLeft);
        checkForCircleEvent(arcRight);
    }

    private void checkForCircleEvent(Arc arc) {
        Point circleCenter = arc.checkCircle();
        if (circleCenter != null) {
            double radius = arc.site.distanceTo(circleCenter);
            Point circleEventPoint = new Point(circleCenter.x, circleCenter.y - radius);
            CircleEvent circleEvent = new CircleEvent(arc, circleEventPoint, circleCenter);
            arcs.put(arc, circleEvent);
            events.add(circleEvent);
        }
    }

    private void show() {
        StdDraw.clear();
        for (Point p : sites) {
            p.draw(StdDraw.RED);
        }
        for (VoronoiEdge edge : edgeList) {
            if (edge.pointLeft != null && edge.pointRight != null) {
                double topY = (edge.pointLeft.y == Double.POSITIVE_INFINITY) ? MAX_DIM : edge.pointLeft.y;
                StdDraw.line(edge.pointLeft.x, topY, edge.pointRight.x, edge.pointRight.y);
            }
        }
        StdDraw.show();
    }
}
