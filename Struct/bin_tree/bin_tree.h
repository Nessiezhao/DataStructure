#pragma once
#include<stdio.h>
typedef char TreeNodeType;

//使用孩子表示法来表示一个树
typedef struct TreeNode
{
    TreeNodeType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

//对于链表来说，使用链表的头节点的指针表示一个链表
//对于一个树来书，使用根节点的指针来表示一个树
void TreeInit(TreeNode** pRoot);

void TreePreOrder(TreeNode* root);
void TreeInOrder(TreeNode* root);
void TreePostOrder(TreeNode* root);
void TreeLevelOrder(TreeNode* root);
//输入一个数组（数组的每个元素就是树上的节点）
//根据数组的内容构建出一个树，数组中的内容符合树的先序遍历
//所有空节点用#表示
TreeNode* TreeCreate(TreeNodeType data[],size_t size,char null_node);
//一般深拷贝为clone，浅拷贝为copy
TreeNode* TreeClone(TreeNode* root);
