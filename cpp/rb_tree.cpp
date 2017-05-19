#include "rb_tree.h"

void RB_Tree::Insert(TreeNode* z){

    TreeNode* y = NULL;
    TreeNode* x = root;
    while(x!=y){
        y=x;
        if(z->data<x->data) x=x->lchild;
        if(z->data>x->data) x=x->rchild;
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

    while(z->parent->color==RED){

        if(z->parent==z->parent->parent->left){

            y=z->parent->parent->rchild;

            if(y->color==RED){ // case 1
                z->parent->color=BLACK;
                y->color=BLACK;
                z->parent->parent->color=RED;
                z=z->parent->parent;

            }else if(z==z->parent->rchild){// case 2
                z=z->parent;
                LeftRotate(z);

            }else{// case 3
                z->parent->color=BLACK;
                z->parent->parent->color=RED;
                RightRotate(z->parent->parent);
            }
        }
    }

    root->color=>BLACK;
}

