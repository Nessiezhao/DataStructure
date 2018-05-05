#include <stdio.h>
#include"bin_tree.h"
#include"seqqueue.h"
#include"seqstack.h"
#include<stdlib.h>
#include<stddef.h>

TreeNode* CreateTreeNode(TreeNodeType value)
{
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}
void DestroyTreeNode(TreeNode* node)
{
    free(node);
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
//销毁的过程要保证能正确找到左右子树
void TreeDestroy(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    TreeDestroy(root->lchild);
    TreeDestroy(root->rchild);
    DestroyTreeNode(root);
    return;
}
//求一个树有多少个节点，方法一：代码比较容易想，较直观
void _TreeSize(TreeNode* root,size_t* size)
{
    if(root == NULL || size == NULL)
    {
        return;
    }
    ++(*size);
    _TreeSize(root->lchild,size);
    _TreeSize(root->rchild,size);
}
size_t TreeSize1(TreeNode* root)
{
    size_t size = 0;
    _TreeSize(root,&size);
    return size;
}
//方法二：代码比较少
size_t TreeSize2(TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    return 1 + TreeSize2(root->lchild) + TreeSize2(root->rchild);
}
//求一个树中叶子结点的个数
size_t TreeLeafSize(TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    if(root->lchild == NULL && root->rchild == NULL)
    {
        return 1;
    }
    return TreeLeafSize(root->lchild) + TreeLeafSize(root->rchild);
}
//求一个二叉树第K层节点的个数
size_t TreeKLevelSize(TreeNode* root,int K)
{
    if(root == NULL || K < 1)
    {
        return 0;
    }
    if(K == 1)
    {
        return 1;
    }
    return TreeKLevelSize(root->lchild,K-1) + TreeKLevelSize(root->rchild,K-1);
}
size_t TreeHeight(TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    size_t lheight = TreeHeight(root->lchild);
    size_t rheight = TreeHeight(root->rchild);
    return 1 + (lheight > rheight ? lheight : rheight);
}
//此处访问操作相当于visit
TreeNode* TreeNodeFind(TreeNode* root,TreeNodeType to_find)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(root->data == to_find)
    {
        return root;
    }
    TreeNode* lnode = TreeNodeFind(root->lchild,to_find);
    TreeNode* rnode = TreeNodeFind(root->rchild,to_find);
    return lnode != NULL ? lnode : rnode;
}
TreeNode* LChild(TreeNode* root)
{
    if(root == NULL)
    {
        return NULL;
    }
    return root->lchild;
}
TreeNode* RChild(TreeNode* root)
{
    if(root == NULL)
    {
        return NULL;
    }
    return root->rchild;
}
//查找父节点
TreeNode* TreeParent(TreeNode* root,TreeNode* child)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    if(child == NULL)
    {
        //非法输入
        return NULL;
    }
    if(root->lchild == child || root->rchild == child)
    {
        return root;
    }
    TreeNode* lnode = TreeParent(root->lchild,child);
    TreeNode* rnode = TreeParent(root->rchild,child);
    return lnode != NULL ? lnode : rnode;
}
////////////////////////////////////////////////////////////////////////
//以下为笔试面试常见题
//////////////////////////////////////////////////////////////////////
#if 0
void TreePreOrderByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    //先把根结点入栈
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,root);
    //循环开始，栈为空时循环结束
    TreeNode* cur = NULL;
    while(SeqStackTop(&stack,&cur))
    {
        //取栈顶元素为当前元素。出栈
        SeqStackPop(&stack);
        //打印当前元素
        printf("%c ",cur->data);
        //把当前元素的左子树入栈
        if(cur->rchild != NULL)
        {
            SeqStackPush(&stack,cur->rchild);
        }
        //把当前的右子树入栈
        if(cur->lchild != NULL)
        {
            SeqStackPush(&stack,cur->lchild);
        }
    }
    printf("\n");
    return;
}

void TreeInOrderByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    //定义cur指向根节点
    TreeNode* cur = root;
    while(1)
    {
        //循环的判定cur是否为空，如果不为空，就将cur入栈
        //并将cur指向cur->lchild
        while(cur != NULL)
        {
            SeqStackPush(&stack,cur);
            cur = cur->lchild;
        }
        //如果cur为空，取栈顶元素，访问出栈
        TreeNode* top;
        int ret = SeqStackTop(&stack,&top);
        if(ret == 0)
        {
            //说明栈中已经没有元素了
            return;
        }
        printf("%c ",top->data);
        SeqStackPop(&stack);
        //让cur指向栈顶元素的右子树，重复刚才循环判空的过程
        cur = cur->rchild;
    }
    printf("\n");
    return;
}
void TreePostOrderByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    //定义一个cur指向root
    TreeNode* cur = root;
    //pre保存上一个访问过的元素
    TreeNode* pre = NULL;
    while(1)
    {
        //循环判断cur是否为空，如果不为空就将cur入栈
        //并且将cur指向cur->lchild
        while(cur != NULL)
        {
            SeqStackPush(&stack,cur);
            cur = cur->lchild;
        }
        TreeNode* top;
        int ret = SeqStackTop(&stack,&top);
        if(ret == 0)
        {
            printf("\n");
            return;
        }
        //如果cur为空，循环取栈顶元素
        //对栈顶元素进行判定
        //a）如果栈顶元素的右子树和访问的上一个元素是同一个元素
        //b）栈顶元素的右子树为空
        //   此时才能够访问栈顶元素，同时进行出栈
        //如果不满足刚才的条件，就让cur指向栈顶元素的右子树，重复循环
        if(top->rchild == NULL || top->rchild == pre)
        {
            printf("%c ",top->data);
            SeqStackPop(&stack);
            pre = top;
        }
        else
        {
            cur = top->rchild;
        }
    }
    return;
}
void Swap(TreeNode** a,TreeNode** b)
{
    TreeNode* tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void TreeMirror(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    Swap(&root->lchild,&root->rchild);
    TreeMirror(root->lchild);
    TreeMirror(root->rchild);
}
void TreeMirrorByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,root);
    TreeNode* cur = NULL;
    while(SeqQueueFront(&queue,&cur))
    {
        //此处的访问相当于交换左右子树
        Swap(&cur->lchild,&cur->rchild);
        SeqQueuePop(&queue);
        if(cur->lchild != NULL)
        {
            SeqQueuePush(&queue,cur->lchild);
        }
        if(cur->rchild != NULL)
        {
            SeqQueuePush(&queue,cur->rchild);
        }
    }
    return;
}
#endif
int IsCompleteTree(TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,root);
    //是否要进入第二阶段
    int is_step_tow_flag = 0;
    TreeNode* cur = NULL;
    while(SeqQueueFront(&queue,&cur))
    {
        SeqQueuePop(&queue);
        //阶段一走这个分支
        if(is_step_tow_flag == 0)
        {
            if(cur->lchild != NULL && cur->rchild != NULL)
            {
                //同时具备左右子树
                SeqQueuePush(&queue,cur->lchild);
                SeqQueuePush(&queue,cur->rchild);
            }
            else if(cur->rchild != NULL && cur->lchild == NULL)
            {
                //只有右子树，没有左子树，一定不是完全二叉树
                return 0;
            }
            else if(cur->rchild == NULL && cur->lchild != NULL)
            {
                //只有左子树没有右子树，需要进入第二阶段
                is_step_tow_flag = 1;
                SeqQueuePush(&queue,cur->lchild);
            }
            else
            {
                //没有左右子树
                is_step_tow_flag = 1;
            }
        }
        else
        {
            //阶段二分支
            if(cur->lchild == NULL && cur->rchild == NULL)
            {
                ;
            }
            else
            {
                return 0;
            }
        }//结束阶段一和阶段二的判定
    }//循环结束
    //所有节点都遍历完了，此时是完全二叉树
    return 1;
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
void TestDestroy()
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
    TreeDestroy(a);
    return;
}
void TestSize1()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    size_t size = TreeSize1(root);
    printf("size: expected is 7, actual %lu\n",size);
}
void TestSize2()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    size_t size = TreeSize2(root);
    printf("size: expected is 7, actual %lu\n",size);
}
void TestLeafSize()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    size_t size = TreeLeafSize(root);
    printf("size: expected is 3, actual %lu\n",size);

}
void TestKLevelSize()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    size_t size = TreeKLevelSize(root,3);
    printf("size: expected is 3,actual %lu\n",size);
}
void TestHeight()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    size_t size = TreeHeight(root);
    printf("size: expected is 4 ,actual %lu\n",size);
}
void TestNodeFind()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    TreeNode* node = TreeNodeFind(root,'g');
    printf("node: expected is %p,actual %p\n",root->lchild->rchild->lchild,node);
}
void TestParent()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    TreeNode* child = root->lchild->rchild;
    TreeNode* node = TreeParent(root,child);
    printf("node: expected is %p,actual %p\n",root->lchild,node);

}
#if 0
void TestPreOrderByLoop()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    TreePreOrderByLoop(root);
}
void TestInOrderByLoop()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    TreeInOrderByLoop(root);
}
void TestPostOrderByLoop()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    TreePostOrderByLoop(root);
}
void TestMirror()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    TreeMirror(root);
    printf("\n先序遍历：");
    TreePreOrder(root);
    printf("\n中序遍历：");
    TreeInOrder(root);
    printf("\n后序遍历：");
    TreePostOrder(root);
    printf("\n层序遍历：");
    TreeLevelOrder(root);
}
void TestMirrorByLoop()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    TreeMirrorByLoop(root);
    printf("\n先序遍历：");
    TreePreOrder(root);
    printf("\n中序遍历：");
    TreeInOrder(root);
    printf("\n后序遍历：");
    TreePostOrder(root);
    printf("\n层序遍历：");
    TreeLevelOrder(root);
}
#endif
void TestIsComplete()
{
    TEST_HEADER;
    TreeNodeType data[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(data,sizeof(data)/sizeof(data[0])-1,'#');
    int ret = IsCompleteTree(root);
    printf("ret expected : 0,actual %d\n",ret);
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
    TestDestroy();
    TestSize1();
    TestSize2();
    TestLeafSize();
    TestKLevelSize();
    TestHeight();
    TestNodeFind();
    TestParent();
 //   TestPreOrderByLoop();
 //   TestInOrderByLoop();
 //   TestPostOrderByLoop();
 //   TestMirror();
 //   TestMirrorByLoop();
    TestIsComplete();
    return 0;
}
#endif
