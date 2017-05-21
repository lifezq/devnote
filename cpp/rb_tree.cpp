#include "rb_tree.h"
#include <stack>


void RB_Tree::Insert(TreeNode* z){


    TreeNode* y = NULL;
    TreeNode* x = root;
    while(x!=NULL){
        y=x;

        if(z->data<x->data) 
            x=x->lchild;
        else if(z->data>x->data) 
            x=x->rchild;
    }


    z->parent=y;

    if(NULL==y){
        root=z;
    }else if(z->data<y->data){
        y->lchild=z;
    }else{
        y->rchild=z;
    }

    z->lchild=NULL;
    z->rchild=NULL;
    z->color = RED;

    InsertFixup(z);
}


/*--fixup case:-------------------------------------------------------------------
 *  1. 如果当前结点的父结点是红色且祖父结点的另一个子结点（叔叔结点）是红色
 *  2. 当前结点的父结点是红色,叔叔结点是黑色，当前结点是其父结点的右子
 *  3. 当前结点的父结点是红色,叔叔结点是黑色，当前结点是其父结点的左子
 *-----------------------------------------------------------------------------*/
void RB_Tree::InsertFixup(TreeNode* z){
    TreeNode* y;

    if(z->parent==NULL){
        root->color=BLACK;
        return;
    }

    while(z->parent!=NULL && z->parent->color==RED){


        if(z->parent==z->parent->parent->lchild){


            y=z->parent->parent->rchild;

            if(y!=NULL && y->color==RED){ // case 1
                z->parent->color=BLACK;
                y->color=BLACK;
                z->parent->parent->color=RED;
                z=z->parent->parent;

            }else{

                if(z==z->parent->rchild){// case 2
                    z=z->parent;
                    LeftRotate(z);
                }

                // case 3
                z->parent->color=BLACK;
                z->parent->parent->color=RED;
                RightRotate(z->parent->parent);
            }
        }else{
            y=z->parent->parent->lchild;
            if(y!=NULL && y->color==RED){
                z->parent->color=BLACK;
                y->color=BLACK;
                z->parent->parent->color=RED;
                z=z->parent->parent;
            }else{

                if(z==z->parent->lchild){
                    z=z->parent;
                    RightRotate(z);
                }


                z->parent->color=BLACK;
                z->parent->parent->color=RED;
                LeftRotate(z->parent->parent);
            }
        }
    }

    root->color=BLACK;
}

void RB_Tree::LeftRotate(TreeNode* x){
    TreeNode* y=x->rchild;
    x->rchild=y->lchild;
    if(y->lchild!=NULL){
        y->lchild->parent=x;
    }

    y->parent=x->parent;
    if(x->parent==NULL){
        root=y;
    }else if(x==x->parent->lchild) x->parent->lchild=y;
    else x->parent->rchild=y;
    y->lchild=x;
    x->parent=y;
}

void RB_Tree::RightRotate(TreeNode* x){
    TreeNode* y=x->lchild;
    x->lchild=y->rchild;
    if(y->rchild!=NULL){
        y->rchild->parent=x;
    }

    y->parent=x->parent;
    if(x->parent==NULL){
        root=y;
    }else if(x==x->parent->lchild) x->parent->lchild=y;
    else x->parent->rchild=y;
    y->rchild=x;
    x->parent=y;
}

/*-----------------------------------------------------------------------------
 *  1. 没有儿子，即为叶结点。直接把父结点的对应儿子指针设为NULL，删除儿子结点就OK了。
 *  2. 只有一个儿子。那么把父结点的相应儿子指针指向儿子的独生子，删除儿子结点也OK了。
 *  3. 有两个儿子。我们可以选择左儿子中的最大元素或者右儿子中的最小元素放到待删除
 *     结点的位置，就可以保证结构的不变。
 *-----------------------------------------------------------------------------*/
TreeNode* RB_Tree::Delete(TreeNode* z){
    TreeNode* y;
    TreeNode* x;
    if(z->lchild == NULL || z->rchild == NULL) y=z;
    else y=TreeSuccessor(z);

    if(y->lchild != NULL) x=y->lchild;
    else x=y->rchild;

    x->parent=y->parent;
    if(y->parent == NULL) root=x;
    else if(y==y->parent->lchild) y->parent->lchild=x;
    else y->parent->rchild=x;

    if(y!=z) z->data=y->data;

    if(y->color==BLACK) DeleteFixup(x);

    return y;
}

/*-----------------------------------------------------------------------------
 *  1. 当前结点是黑+黑且兄弟结点为红色(此时父结点和兄弟结点的子结点分为黑)
 *  2. 当前结点是黑加黑且兄弟是黑色且兄弟结点的两个子结点全为黑色
 *  3. 当前结点颜色是黑+黑，兄弟结点是黑色，兄弟的左子是红色，右子是黑色
 *  4. 当前结点颜色是黑-黑色，它的兄弟结点是黑色，但是兄弟结点的右子是红色，
 *     兄弟结点左子的颜色任意
 *-----------------------------------------------------------------------------*/
void RB_Tree::DeleteFixup(TreeNode* x){
    TreeNode* y;
    while(x!=root && x->color==BLACK){
        if(x==x->parent->lchild){
            y=x->parent->rchild;
            if(y->color==RED){// case 1
                y->color=BLACK;
                x->parent->color=RED;
                LeftRotate(x->parent);
                y=x->parent->rchild;
            }
            if(y->lchild->color==BLACK && y->rchild->color==BLACK){ // case 2
                y->color=RED;
                x=x->parent;
            }else if(y->rchild->color==BLACK){// case 3
                y->rchild->color=BLACK;
                y->color=RED;
                RightRotate(y);
                y=x->parent->rchild;
            }else{// case 4
                y->color=x->parent->color;
                x->parent->color=BLACK;
                y->rchild->color=BLACK;
                LeftRotate(x->parent);
                x=root;
            }
        }
    }

    x->color=BLACK;
}

TreeNode* RB_Tree::TreeSuccessor(TreeNode* x){
    if(x->rchild!=NULL) return TreeMinimum(x->rchild);
    TreeNode* y=x->parent;
    while(y!=NULL && x==y->rchild){
        x=y;
        y=y->parent;
    }

    return y;
}

TreeNode* RB_Tree::TreeMinimum(TreeNode* x){
    while(x->lchild!=NULL) x=x->lchild;
    return x;
}

void RB_Tree::InorderTravel(TreeNode* n){

    if(NULL == n) return;

        cout <<  n->data << "(" << n->color << ") ";

    if(n->lchild){
        InorderTravel(n->lchild);
    }

    if(n->rchild){
        InorderTravel(n->rchild);
    }
}

void RB_Tree::InOrderTraverse(){
    stack<TreeNode*> stk;
    TreeNode* p = root;
    while(p!=NULL || !stk.empty()){
        while(p!=NULL){
            stk.push(p);
            p=p->lchild;
        }

        if(!stk.empty()){
            cout << stk.top()->data << "(" << stk.top()->color << ")" << " ";
            p=stk.top()->rchild;
            stk.pop();
        }
    }
}

int main(){

    int arr[20]={12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17};
    RB_Tree rb =  RB_Tree();
    for(int i=0;i<20;i++) rb.Insert(new TreeNode(arr[i]));

    rb.InOrderTraverse();
    cout << endl;
    rb.InorderTravel(rb.root);
    cout << endl;
    return 0;
}
