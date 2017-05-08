#include<deque>
#include<iostream>
using namespace std;

typedef struct TreeNode{
    int data;
    struct TreeNode *left,*right;
    TreeNode(int n):data(n),left(NULL),right(NULL){};
}TreeNode,*TreePtr;

void createTree(TreePtr &root){
    int data;
    cin >> data;
    if(data == 0) return;
    
    root = new TreeNode(data);

    cout << "Input left node(int):";
    createTree(root->left);

    cout << "Input right node(int):";
    createTree(root->right);
}

void travelTree(TreePtr root){
    if(root == NULL) return;


    cout << "node val:" << root->data << endl;

    if(root->left){
        cout << "node left val:" << root->left->data << endl;
        travelTree(root->left);
    }
    if(root->right){
        cout << "node right val:" << root->right->data << endl;
        travelTree(root->right);
    }
}

TreePtr invertTree(TreePtr root){

    if(root == NULL) return root;
    
    TreePtr left = root->left;
    TreePtr right = root->right;

    root->left = invertTree(right);

    root->right = invertTree(left);
    
    return root;
}

//TreePtr invertTreeViaDeque(TreePtr root){
//   if(root == NULL) return root;

//    deque<TreePtr> stack;
//}


int main(){

    deque<int> stack;
    for(int i=0;i<10;i++)
    stack.push_back(i);


    for(int i=0;i<10;i++){

        int num = stack.back();
        stack.pop_back();
        cout << "num:" << num << endl;
    }

    
    return 0;
    TreePtr root;
    cout << "Input root node(int):";
    createTree(root);

    cout << "-------------------------" << endl;
    travelTree(root);

    root = invertTree(root);

    cout << "-------------------------" << endl;
    travelTree(root);
}
