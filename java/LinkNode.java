public class LinkNode {

    public static Node node;

    public static void main(String[] args) {
        build();
        traversal(node);
        node = reverse(node);
        traversal(node);
        //再次反转，将链表恢复为初始状态
        node = reverse(node);
        System.out.println("**************************************");
        traversal(node);
        Node n2 = reverseKM(node, 2, 4);
        System.out.println("链表中间反转后遍历：");
        traversal(n2);

        build();
        Node n3 = merge(node, n2);
        System.out.println("链表合并后遍历：");
        traversal(n3);
    }

    public static void build() {
        node = new Node(1);
        node.next = new Node(2);
        node.next.next = new Node(3);
        node.next.next.next = new Node(4);
        node.next.next.next.next = new Node(5);
        node.next.next.next.next.next = new Node(6);
    }

    //1->2->3->4->5->6->null
    public static Node reverse(Node n) {
        Node temp = null;
        Node head = null;
        while (n != null) {
            temp = n.next;
            n.next = head;
            head = n;
            n = temp;
        }

        return head;
    }

    public static Node reverseKM(Node n, int k, int m) {
        Node head = n;
        Node newNode = null;
        Node tailNode = n;
        Node headNode = null;
        Node temp = null;
        int idx = 1;
        while (n != null) {

            if (idx + 1 == k) {
                tailNode = n;
            }

            if (idx >= k && idx <= m) {

                temp = n.next;
                n.next = newNode;
                newNode = n;
                n = temp;
                idx++;
                continue;
            }

            if (idx == m + 1) {
                headNode = n;
            }

            if (idx >= m) {
                tailNode.next = newNode;
            }

            n = n.next;
            idx++;
        }

        temp = newNode;
        while (temp.next != null) {
            temp = temp.next;
        }

        temp.next = headNode;

        return head;
    }

    public static Node merge(Node n1, Node n2) {
        Node head = n1;
        if (n1 == null) {
            return n2;
        }

        if (n2 == null) {
            return n1;
        }

        while (n1.next != null) {
            n1 = n1.next;
        }

        n1.next = n2;
        return head;
    }

    public static void traversal(Node n) {
        System.out.println("遍历链表：");
        while (n != null) {
            System.out.print(n.data + "->");
            n = n.next;
        }

        System.out.println("");
    }

    static class Node {
        public int data;
        public Node next;

        Node() {

        }

        Node(int data) {
            this.data = data;
        }
    }
}
