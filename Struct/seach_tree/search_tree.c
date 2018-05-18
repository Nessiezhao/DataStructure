#include <stdio.h>
#include<stdlib.h>
#include"search_tree.h"
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

int main()
{
    TestInit();
    return 0;
}
#endif
