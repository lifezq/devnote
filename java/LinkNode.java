public class LinkNode {

    public static Node node;

    public static void main(String[] args) {
        build();
        node = reverse(node);
        traversal(node);
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
