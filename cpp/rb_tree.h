#ifndef _RB_TREE_H
#define _RB_TREE_H
#include <iostream>
using namespace std;

/*--红黑树五性质:-----------------------------------------------------------------
 *  1. 每个结点要么是红的，要么是黑的。
 *  2. 根结点是黑的。 
 *  3. 每个叶节点（叶节点即指树尾端NIL指针或NULL结点）是黑的。   
 *  4. 如果一个结点是红的，那么它的俩个儿子都是黑的。
 *  5. 对于任一结点而言，其到叶结点树尾端NIL指针的每一条路径都包含相同数目的黑结点。
 *-----------------------------------------------------------------------------*/

enum RB_Color {RED, BLACK};

class TreeNode{
        friend class RB_Tree;
    public:
        TreeNode(): data(0), color(BLACK), parent(NULL), lchild(NULL), rchild(NULL){}
        TreeNode(int x): data(x), color(BLACK), parent(NULL), lchild(NULL), rchild(NULL){}
        TreeNode(const TreeNode* n){
            data=n->data;
            color=n->color;
            parent=n->parent;
            lchild=n->lchild;
            rchild=n->rchild;
        }
        ~TreeNode(){
            parent=NULL;
            lchild=NULL;
            rchild=NULL;
        }
    private:
        int data;
        RB_Color color;
        TreeNode *parent;
        TreeNode *lchild;
        TreeNode *rchild;
};

class RB_Tree{
    public:
        TreeNode* root;
        RB_Tree(){
            root=NULL;
        }
        ~RB_Tree(){
            root=NULL;
        }
        void Insert(TreeNode *n);
        TreeNode* Delete(int data);
        TreeNode* Delete(TreeNode *n);
        void Traverse(TreeNode* n, int order);
        void InOrderTraverse();
        TreeNode* Search(TreeNode* n, int data);
    private:
        void InsertFixup(TreeNode *n);
        void LeftRotate(TreeNode *n);
        void RightRotate(TreeNode *n);
        void DeleteFixup(TreeNode *n);
        TreeNode* TreeSuccessor(TreeNode *n);
        TreeNode* TreeMinimum(TreeNode *n);
};

#endif
