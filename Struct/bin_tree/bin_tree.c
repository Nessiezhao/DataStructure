#include <stdio.h>
#include"bin_tree.h"
#include"seqqueue.h"
#include<stdlib.h>

TreeNode* CreateTreeNode(TreeNodeType value)
{
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}
void TreeInit(TreeNode** pRoot)
{
    if(pRoot == NULL)
    {
        //非法输入
        return;
    }
    if(*pRoot == NULL)
    {
        //空树
        return;
    }
    *pRoot = NULL;
    return;
}
void TreePreOrder(TreeNode* root)
{
    if(root == NULL)
    {
        printf("#");
        return;
    }
    //先访问根结点，再左子树，再右子树
    printf("%c",root->data);
    TreePreOrder(root->lchild);
    TreePreOrder(root->rchild);
    return;
}
void TreeInOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    //先遍历左子树，再遍历根节点，最后遍历右子树
    TreeInOrder(root->lchild);
    printf("%c",root->data);
    TreeInOrder(root->rchild);
    return;
}
void TreePostOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    //先遍历左子树，再遍历右子树，最后访问根结点
    TreePostOrder(root->lchild);
    TreePostOrder(root->rchild);
    printf("%c",root->data);
    return;
}
void TreeLevelOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,root);
    while(1)
    {
        SeqQueueType front;
        int ret = SeqQueueFront(&queue,&front);
        if(ret == 0)
        {
            //如果取队列首元素失败，说明队列为空
            //如果队列为空，说明遍历已经结束
            break;
        }
        printf("%c",front->data);
        SeqQueuePop(&queue);
        if(front->lchild != NULL)
        {
            SeqQueuePush(&queue,front->lchild);
        }
        if(front->rchild != NULL)
        {
            SeqQueuePush(&queue,front->rchild);
        }
    }
    printf("\n");
    return;
}
TreeNode* _TreeCreate(TreeNodeType data[],size_t size,size_t* index,TreeNodeType null_node)
{
    if(index == NULL)
    {
        return NULL;
    }
    if((*index) >= size)
    {
        return NULL;
    }
    if(data[*index] == null_node)
    {
        return NULL;
    }
    TreeNode* new_node = CreateTreeNode(data[*index]);
    ++(*index);
    new_node->lchild = _TreeCreate(data,size,index,null_node);
    ++(*index);
    new_node->rchild = _TreeCreate(data,size,index,null_node);
    return new_node;
}
TreeNode* TreeCreate(TreeNodeType data[],size_t size,char null_node)
{
    size_t index = 0;//表示当前取数组的哪个元素
    return _TreeCreate(data,size,&index,null_node);
}
TreeNode* TreeClone(TreeNode* root)
{
    if(root == NULL)
    {
        return NULL;
    }
    TreeNode* new_node = CreateTreeNode(root->data);
    new_node->lchild = TreeClone(root->lchild);
    new_node->rchild = TreeClone(root->rchild);
    return new_node;
}
////////////////////////////////////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n======================%s========================\n",__FUNCTION__);
void TestInit()
{
    TEST_HEADER;
    TreeNode* bin_tree;
    TreeInit(&bin_tree);
}
void TestPreOrder()
{
    TEST_HEADER;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->lchild = f;
    TreePreOrder(a);
    return;
}
void TestInOrder()
{
    TEST_HEADER;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->lchild = f;
    TreeInOrder(a);
    return;
}
void TestPostOrder()
{
    TEST_HEADER;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->lchild = f;
    TreePostOrder(a);
    printf("\n");
    return;
}
void TestLevelOrder()
{
    TEST_HEADER;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->lchild = f;
    TreeLevelOrder(a);
    printf("\n");
    return;
}
void TestCreate()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    printf("\n先序遍历：");
    TreePreOrder(root);
    printf("\n中序遍历：");
    TreeInOrder(root);
    printf("\n后序遍历：");
    TreePostOrder(root);
    printf("\n层序遍历：");
    TreeLevelOrder(root);
    printf("\n");
    return;
}
void TestClone()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    TreeNode* new_root = TreeClone(root);
    printf("\n先序遍历：");
    TreePreOrder(new_root);
    printf("\n中序遍历：");
    TreeInOrder(new_root);
    printf("\n后序遍历：");
    TreePostOrder(new_root);
    printf("\n层序遍历：");
    TreeLevelOrder(new_root);
    printf("\n");
    return;
}
int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    TestLevelOrder();
    TestCreate();
    TestClone();
    return 0;
}
#endif
