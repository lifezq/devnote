#include<iostream>

using namespace std;

typedef struct Lnode {
    int data;
    struct Lnode *next;
}Lnode,*LinkNode;

LinkNode createLnode(int n){

    LinkNode head = (LinkNode)malloc(sizeof(Lnode)),l;

    l = head;

    while(n>0){
        LinkNode tmp = (LinkNode)malloc(sizeof(Lnode));

        cout << "Input node val(int):";
        cin >> tmp->data;

        l->next = tmp;

        l = tmp;

        n--;
    }

    l->next = NULL;

    return head;
}

LinkNode reverseNode(LinkNode head){
    if(head == NULL || head->next ==NULL) return head;
    LinkNode p1, p2, p3;

    p1 = head;
    p2 = head->next;

    while(p2 != NULL){
        p3 = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p3;
    }

    head->next = NULL;

    head = p1;

    return head;
}

LinkNode reverse(LinkNode head){

        if(head == NULL || head->next == NULL) return head;
        LinkNode p=head, newH=NULL;
        while(p!=NULL){
                LinkNode tmp=p->next;//暂存p下一个地址，防止变化指针后找不到后续的数
                p->next=newH;//p->next指向前一个空间
                newH=p;//新链表的头移动到p，扩长一步链表
                p=tmp;//p指向原始链表p指向的下一个空间

        }

        return newH;
}

void traverseNode(LinkNode n){
    if(n ==NULL) return;

    cout << "Node val:" << n->data << endl;
    
    traverseNode(n->next);
}

int main(){

    int nlen;
    cout << "Input linknode length:";
    cin >> nlen;

    LinkNode n = createLnode(nlen);

    cout << "--------------------------------" << endl;

    traverseNode(n);

    cout << "--------------------------------" << endl;

    traverseNode(reverse(n));
    return 0;
}
