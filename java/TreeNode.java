import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

class TreeNode {

    private static Node node;

    public static void main(String[] args) {
        buildTree();
        middleTraversal2(node);
        System.out.println("\n----------------------");
    }

    /*
     *                   22
     *               /       \
     *             20         24
     *          /      \   /      \
     *       19        21 23      25
     */
    public static void buildTree() {
        node = new Node(22);
        node.left = new Node(20);
        node.left.left = new Node(19);
        node.left.right = new Node(21);
        node.right = new Node(24);
        node.right.left = new Node(23);
        node.right.right = new Node(25);
    }

    public static void middleTraversal(Node n) {
        if (n == null) {
            return;
        }
        middleTraversal(n.left);
        System.out.print(n.data + "->");
        middleTraversal(n.right);
    }

    public static void middleTraversal2(Node n) {
        if (n == null) {
            return;
        }

        List<Integer> vals = new ArrayList<>();
        Stack<Node> s = new Stack<>();
        while (n != null || !s.isEmpty()) {
            while (n != null) {
                s.push(n);
                n = n.left;
            }

            if (!s.isEmpty()) {
                n = s.pop();
                vals.add(n.data);
                n = n.right;
            }
        }

        vals.forEach(x -> {
            System.out.print(x + "-");
        });
    }

    public static void prevTraversal(Node n) {

    }

    static class Node {
        public int data;
        public Node left;
        public Node right;

        Node() {

        }

        Node(int data) {
            this.data = data;
        }
    }
}