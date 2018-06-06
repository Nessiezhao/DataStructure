#pragma once
typedef char SearchNodeType;

typedef struct SearchNode
{
    SearchNodeType data;
    struct SearchNode* lchild;
    struct SearchNode* rchild;
}SearchNode;

void SearchTreeInit(SearchNode** pRoot);
void SearchTreeDestroy(SearchNode** pRoot);
void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert);
void PreOrder(SearchNode* root);
void Inorder(SearchNode* root);
SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find);
