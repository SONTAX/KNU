public class Query {
    private final int N = 9;

    public void case1() {
        RangeSearch rangeSearch = new RangeSearch();
        rangeSearch.build(1, N);
        rangeSearch.add(1, 7);
        rangeSearch.add(2, 3);
        rangeSearch.add(3, 8);
        rangeSearch.add(4, 4);
        rangeSearch.add(5, 9);
        rangeSearch.add(6, 6);
        rangeSearch.add(7, 1);
        rangeSearch.add(8, 2);
        rangeSearch.query(new Interval2D(new Interval(2, 7), new Interval(3, 7)));
    }

    public void case2() {
        RangeSearch rangeSearch = new RangeSearch();
        rangeSearch.build(1, N);
        rangeSearch.add(1, 5);
        rangeSearch.add(2, 3);
        rangeSearch.add(3, 1);
        rangeSearch.add(4, 2);
        rangeSearch.query(new Interval2D(new Interval(4, 7), new Interval(1, 5)));
    }

    public void case3() {
        RangeSearch rangeSearch = new RangeSearch();
        rangeSearch.build(1, N);
        rangeSearch.add(1, 7);
        rangeSearch.add(2, 3);
        rangeSearch.add(3, 8);
        rangeSearch.add(4, 4);
        rangeSearch.add(5, 9);
        rangeSearch.add(6, 6);
        rangeSearch.add(7, 1);
        rangeSearch.add(8, 2);
        rangeSearch.query(new Interval2D(new Interval(3, 6), new Interval(5, 7)));

    }

    public static void main(String[] args) {
        Query query = new Query();
        System.out.println("1.");
        query.case1();
        System.out.println("2.");
        query.case2();
        System.out.println("3.");
        query.case3();
    }
}
