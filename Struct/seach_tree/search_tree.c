#include <stdio.h>
#include<stdlib.h>
#include"search_tree.h"
//常见的题
//给定一个数组，再给你一个数字，让你判定数字是否在数组之中
//给定一个数组，数字可能存在重复元素，去重
//给定一个数组，数字可能存在重复，统计每个重复数字出现的次数
//给你一段英文，翻译成中文，给你一个中英文对照表
void SearchTreeInit(SearchNode** pRoot)
{
    if(pRoot == NULL)
    {
        //非法输入
        return;
    }
    *pRoot = NULL;
    return;
}
void DestroySearchNode(SearchNode* root)
{
    free(root);
}
void SearchTreeDestroy(SearchNode** pRoot)
{
    //此处的销毁和销毁一个普通的二叉树一样
    //这里我们采用后序遍历的方式来销毁这个树
    if(pRoot == NULL)
    {
        return;
    }
    if(*pRoot == NULL)
    {
        return;
    }
    SearchNode* root = *pRoot;
    SearchTreeDestroy(&root->lchild);
    SearchTreeDestroy(&root->rchild);
    DestroySearchNode(root);
    *pRoot = NULL;
    return;
}
SearchNode* CreateSearchNode(SearchNodeType value)
{
    SearchNode* new_node = (SearchNode*)malloc(sizeof(SearchNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}
void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert)
{
    if(pRoot == NULL)
    {
        //非法输入
        return;
    }
    if(*pRoot == NULL)
    {
        //如果是一个空树，那就直接把要插入的元素插入到根结点，把pRoot指向根结点就可以
        SearchNode* new_node = CreateSearchNode(to_insert);
        *pRoot = new_node;
        return;
    }
    //此时树不为空，采用递归的方式来向树中插入元素
    SearchNode* cur = *pRoot;
    if(to_insert < cur->data)
    {
        //如果要插入的元素比当前节点的值小，就递归的向左子树插入
        SearchTreeInsert(&cur->lchild,to_insert);
    }
    else if(to_insert > cur->data)
    {
        //如果要插入的元素比当前节点的值大，就递归的向右子树中插入
        SearchTreeInsert(&cur->rchild,to_insert);
    }
    else
    {
        //如果要插入的元素值刚好和现在节点的值相等，有很多种处理方式
        //这里采取的是不允许二叉树中存在重复的元素
        //所以如果遇到插入的值刚好和现在结点的值相等的情况
        //就不采取任何操作，直接返回，插入失败
        //也可以采取其他的方式：
        //1.可以把这个元素放到相等元素的左子树的最右边
        //2.可以把这个元素放到相等元素的右子树的最左边
        return;
    }
    return;
}
void PreOrder(SearchNode* root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%c ",root->data);
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}
void Inorder(SearchNode* root)
{
    if(root == NULL)
    {
        return;
    }
    Inorder(root->lchild);
    printf("%c ",root->data);
    Inorder(root->rchild);
}
SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(to_find < root->data)
    {
        //递归的查找左子树
        return SearchTreeFind(root->lchild,to_find);
    }
    if(to_find > root->data)
    {
        //递归的查找右子树
        return SearchTreeFind(root->rchild,to_find);
    }
    return root;
}
void SearchTreeRemove(SearchNode** pRoot,SearchNodeType to_remove)
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
    //1.找到 to_remove 所在的位置
    //如果没找到直接返回
    SearchNode* root = *pRoot;
    if(to_remove < root->data)
    {
        SearchTreeRemove(&root->lchild,to_remove);
        return;
    }
    else if(to_remove > root->data)
    {
        SearchTreeRemove(&root->rchild,to_remove);
        return;
    }
    else
    {
        //如果找到了，分情况讨论
        SearchNode* to_remove_node = root;
        if(root->lchild == NULL && root->rchild == NULL)
        {
            //要删除节点没有子树
            *pRoot = NULL;
            DestroySearchNode(to_remove_node);
            return;
        }
        else if(root->lchild != NULL && root->rchild == NULL)
        {
            //要删除节点只有左子树
            *pRoot = to_remove_node->lchild;
            DestroySearchNode(to_remove_node);
        }
        else if(root->lchild == NULL && root->rchild != NULL)
        {
            //要删除节点只有右子树
            *pRoot = to_remove_node->rchild;
            DestroySearchNode(to_remove_node);
        }
        else
        {
            //要删除节点有左右子树
            //需要先找到右子树中的最小节点
            //把要删除节点的值和最小节点的值进行交换
            //从当前节点的右子树出发
            //尝试递归的删除刚刚被交换的值
            SearchNode* min = to_remove_node->rchild;
            while(min->lchild != NULL)
            {
                min = min->lchild;
            }
            //min 已经指向了右子树中的最小节点
            to_remove_node->data = min->data;
            //尝试递归删除min->data
            SearchTreeRemove(&to_remove_node->rchild,min->data);
            return;
        }
    }
    return;
}
//非递归版本
void SearchTreeInsertByLoop(SearchNode** pRoot,SearchNodeType to_insert)
{
    if(pRoot == NULL)
    {
        return;
    }
    if(*pRoot == NULL)
    {
        *pRoot = CreateSearchNode(to_insert);
        return;
    }
    SearchNode* cur = *pRoot;
    SearchNode* pre = NULL;
    while(1)
    {
        if(cur == NULL)
        {
            break;
        }
        if(to_insert < cur->data)
        {
            pre = cur;
            cur = cur->lchild;
        }
        else if(to_insert > cur->data)
        {
            pre = cur;
            cur = cur->rchild;
        }
        else
        {
            return;
        }
    }
    SearchNode* new_node = CreateSearchNode(to_insert);
    if(new_node->data < pre->data)
    {
        pre->lchild = new_node;
    }
    if(new_node->data > pre->data)
    {
        pre->rchild = new_node;
    }
    return;
}
SearchNode* SearchTreeFindByLoop(SearchNode* root,SearchNodeType to_find)
{
    if(root == NULL)
    {
        return NULL;
    }
    SearchNode* cur = root;
    while(cur != NULL)
    {
        if(to_find > cur->data )
        {
            cur = cur->rchild;
        }
        if(to_find < cur->data)
        {
            cur = cur->lchild;
        }
        else
        {
            break;
        }
    }
    return cur;
}
void SearchTreeRemoveByLoop(SearchNode** pRoot,SearchNodeType to_remove)
{
    if(pRoot == NULL)
    {
        return;
    }
    if(*pRoot == NULL)
    {
        return;
    }
    //先找要删除的节点是谁
    SearchNode* to_remove_node = *pRoot;
    SearchNode* parent = NULL;
    while(1)
    {
        if(to_remove_node == NULL)
        {
            //没找到要删除的节点，函数直接终止
            return;
        }
        if(to_remove < to_remove_node->data)
        {
            parent = to_remove_node;
            to_remove_node = to_remove_node->lchild;
        }
        else if(to_remove > to_remove_node->data)
        {
            parent = to_remove_node;
            to_remove_node = to_remove_node->rchild;
        }
        else
        {
            //找到了要删除的节点
            break;
        }
    }
    //如果找到了要删除的节点，分情况讨论
    if(to_remove_node->lchild == NULL && to_remove_node->rchild == NULL)
    {
        //没有子树
        //此处我们要先判断要删除的节点是否是根结点
        if(to_remove_node == *pRoot)
        {
            //要删除的节点是根结点， parent == NULL
            *pRoot = NULL;
        }
        else
        {
            //要删除元素不是根结点
            //需要知道当前节点是parent的左子树还是右子树
            if(to_remove_node->data < parent->data)
            {
                parent->lchild = NULL;
            }
            else
            {
                parent->rchild = NULL;
            }
        }
        //统一释放节点内存
        DestroySearchNode(to_remove_node);
    }
    else if(to_remove_node->lchild != NULL && to_remove_node->rchild == NULL)
    {
        //只有左子树
        if(to_remove_node == *pRoot)
        {
            *pRoot = to_remove_node->lchild;
        }
        else
        {
            if(to_remove_node->data < parent->data)
            {
                parent->lchild = to_remove_node->lchild;
            }
            else
            {
                parent->rchild = to_remove_node->lchild;
            }
        }
        DestroySearchNode(to_remove_node);
        return;
    }
    else if(to_remove_node->lchild == NULL && to_remove_node->rchild != NULL)
    {
        //只有右子树
        if(to_remove_node == *pRoot)
        {
            *pRoot = to_remove_node->rchild;
        }
        else
        {
            if(to_remove_node->data < parent->data)
            {
                parent->lchild = to_remove_node->rchild;
            }
            else
            {
                parent->rchild = to_remove_node->rchild;
            }
        }
        DestroySearchNode(to_remove_node);
        return;
    }
    else
    {
        //同时有左右子树
        SearchNode* min = to_remove_node->rchild;
        SearchNode* min_parent = to_remove_node;
        while(min->lchild != NULL)
        {
            min_parent = min;
            min = min->lchild;
        }
        //循环结束后，min就指向了to_remove_node右子树的最小值
        to_remove_node->data = min->data;
        if(min->data < min_parent->data)
        {
            //min是min_parent 的左子树
            //min一定没有左子树
            min_parent->lchild = min->rchild;
        }
        else
        {
            //通常情况下，min 是 min_parent 左子树
            //但是出世情况下例外
            min_parent->rchild = min->rchild;
        }
        DestroySearchNode(min);
        return;
    }
    return;
}
//////////////////////////////////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n=============================%s================================\n",__FUNCTION__);
void TestInit()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    printf("root expected NULL,actual %p\n",root);
}
void SearchTreePrintChar(SearchNode* root,const char* msg)
{
    printf("%s\n",msg);
    printf("先序遍历：");
    PreOrder(root);
    printf("\n");
    printf("中序遍历：");
    Inorder(root);
    printf("\n");
}
void TestInsert()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchTreePrintChar(root,"插入5个元素");
}
void TestFind()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchNode* result = SearchTreeFind(root,'c');
    printf("result expected c,actual %c\n",result->data);
}
void TestRemove()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchTreePrintChar(root,"插入5个元素");
    SearchTreeRemove(&root,'d');
    SearchTreePrintChar(root,"删除1个元素");
}
void TestInsertByLoop()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsertByLoop(&root,'a');
    SearchTreeInsertByLoop(&root,'b');
    SearchTreeInsertByLoop(&root,'c');
    SearchTreeInsertByLoop(&root,'d');
    SearchTreeInsertByLoop(&root,'e');
    SearchTreePrintChar(root,"插入5个元素");
}
void TestFindByLoop()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchNode* result = SearchTreeFindByLoop(root,'c');
    printf("result expected c,actual %c\n",result->data);
}
void TestRemoveByLoop()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchTreePrintChar(root,"插入5个元素");
    SearchTreeRemoveByLoop(&root,'d');
    SearchTreePrintChar(root,"删除1个元素");
}
int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    TestInsertByLoop();
    TestFindByLoop();
    TestRemoveByLoop();
    return 0;
}
#endif
