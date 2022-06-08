public class BST {

    private Node root;

    private static class Node {
        private int x;
        private final int y;
        private Node left, right;
        private int N;

        public Node(int y, int x) {
            this.y = y;
            this.x = x;
            this.N = 1;
        }
    }

    public void print() {
        if (root != null) {
            print(root);
        }
    }

    public void put(int y, int x) {
        root = put(root, y, x);
    }

    public int size() {
        return size(root);
    }

    public void search(Interval interval) {
        if (root != null) {
            search(root, interval);
        }
    }

    private void search(Node node, Interval interval) {
        if (node.left != null) {
            if (node.left.y >= interval.min()) {
                search(node.left, interval);
            }
        }
        if (interval.contains(node.y)){
            System.out.println("(" + node.x + ", " + node.y + ")");
        }
        if (node.right != null) {
            if (node.right.y <= interval.max()) {
                search(node.right, interval);
            }
        }
    }

    private Node put(Node node, int key, int val) {
        if (node == null) {
            return new Node(key, val);
        }
        if (node.y == key) {
            node.x = val;
            return node;
        }
        if (key < node.y) {
            node.left = put(node.left, key, val);
        } else {
            node.right = put(node.right, key, val);
        }
        fix(node);
        return node;
    }

    private void print(Node root) {
        if (root.left != null) {
            print(root.left);
        }
        System.out.print("x: " + root.x + ", y: " + root.y + "; ");
        if (root.right != null) {
            print(root.right);
        }
    }

    private int size(Node node) {
        if (node == null) {
            return 0;
        } else {
            return node.N;
        }
    }

    private void fix(Node x) {
        if (x == null) return;
        x.N = 1 + size(x.left) + size(x.right);
    }
}
