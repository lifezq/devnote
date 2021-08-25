import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

class TreeNode {

    private static Node node;

    public static void main(String[] args) {
        buildTree();
        inOrderTraversal2(node);
        System.out.println("\n----------------------");
        middleTraversal(node);
        System.out.println("\n----------------------");

        preOrderTraversal(node);
        System.out.println("\n----------------------");

        postOrderTraversal(node);
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

    public static void inOrderTraversal2(Node n) {
        if (n == null) {
            return;
        }

        List<Integer> vals = new ArrayList<>();
        Stack<Node> s = new Stack<>();
        //依次遍历左节点，将左节点弹出，接着上节点，顺序：左-->上-->右
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

    public static void preOrderTraversal(Node n) {
        if (n == null) {
            return;
        }

        List<Integer> vals = new ArrayList<>();
        Stack<Node> s = new Stack<>();
        s.add(n);
        while (!s.isEmpty()) {

            // 先弹出根节点，向左依次弹出左节点， 顺序 上-->左-->右
            n = s.pop();
            vals.add(n.data);

            if (n.right != null) {
                s.add(n.right);
            }

            if (n.left != null) {
                s.add(n.left);
            }
        }

        vals.forEach(x -> {
            System.out.print(x + "-");
        });
    }

    public static void postOrderTraversal(Node n) {
        if (n == null) {
            return;
        }

        List<Integer> vals = new ArrayList<>();
        Stack<Node> s = new Stack<>();
        Node pre = null;
        s.add(n);
        while (!s.isEmpty()) {
            n = s.peek();
            //叶节点出栈，或者当前节点为之前弹出节点父节点时出栈， 顺序 左-->右-->上
            if (n.left == null && n.right == null ||
                    (pre != null && (pre == n.left || pre == n.right))) {
                vals.add(n.data);
                s.pop();
                pre = n;
            } else {

                if (n.right != null) {
                    s.add(n.right);
                }

                if (n.left != null) {
                    s.add(n.left);
                }
            }
        }

        vals.forEach(x -> {
            System.out.print(x + "-");
        });
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