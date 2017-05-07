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

    traverseNode(reverseNode(n));
    return 0;
}
