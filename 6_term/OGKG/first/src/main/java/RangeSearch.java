public class RangeSearch {

    private Node root;

    private static class Node {
        private final int low;
        private final int high;
        private Node left, right;
        private BST bst;

        public Node(int low, int high) {
            this.low = low;
            this.high = high;
        }
    }

    public void build(int low, int high) {
        root = new Node(low, high);
        root.bst = new BST();
        builder(root, low, high);
    }

    public void add(int x, int y) {
        add(root, x, y);
    }

    public void query(Interval2D rectangle) {
        query(root, rectangle);
    }

    private void query(Node node, Interval2D rectangle) {
        if (node.low == rectangle.intervalX.min() && node.high < rectangle.intervalX.max() ) {
            node.bst.search(rectangle.intervalY);
            /*System.out.println("Checking: [" + node.low + ", " + node.high + ")");*/
            return;
        } else if (node.low > rectangle.intervalX.min() && node.high < rectangle.intervalX.max()) {
            node.bst.search(rectangle.intervalY);
            /*System.out.println("Checking: [" + node.low + ", " + node.high + ")");*/
            return;
        } else if (node.low > rectangle.intervalX.min() && node.high == rectangle.intervalX.max()) {
            node.bst.search(rectangle.intervalY);
            /*System.out.println("Checking: [" + node.low + ", " + node.high + ")");*/
            return;
        }
        if (node.left != null) {
            if (node.left.high > rectangle.intervalX.min()) {
                query(node.left, rectangle);
            }
        }
        if (node.right != null) {
            if (node.right.low <= rectangle.intervalX.max()) {
                query(node.right, rectangle);
            }
        }
    }

    private void add(Node node, int x, int y) {
        if (node.left != null) {
            add(node.left, x, y);
        }
        if (node.low <= x && node.high > x) {
            node.bst.put(y, x);
        }
        if (node.right != null) {
            add(node.right, x, y);
        }
    }

    public void print(Node root) {
        if (root.left != null) {
            print(root.left);
        }
        if (root.left == null && root.right == null) {
            System.out.print("[" + root.low + ", " + root.high + ") ");
            if (root.bst != null ) {
                System.out.print(root.bst.size() + ": ");
                root.bst.print();
            }
            System.out.println();
        }
        if (root.right != null) {
            print(root.right);
        }
    }

    private void builder(Node node, int low, int high) {
        node.bst = new BST();
        if (high - low != 1) {
            node.left = new Node(low, (low + high) / 2);
            builder(node.left, low, (low + high) / 2);
            node.right = new Node((low + high) / 2, high);
            builder(node.right, (low + high) / 2, high);
        }
    }

    /*public static void main(String[] args) {
        RangeSearch RS = new RangeSearch();
        RS.build(1, 9);
        RS.add(1, 7);
        RS.add(2, 3);
        RS.add(3, 8);
        RS.add(4, 4);
        RS.add(5, 9);
        RS.add(6, 6);
        RS.add(7, 1);
        RS.add(8, 2);
        RS.print(RS.root);
        System.out.println("Search:");
        RS.query(new Interval2D(new Interval(2, 7), new Interval(3, 7)));
    }*/
}
