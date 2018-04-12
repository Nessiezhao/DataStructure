#pragma once
#include<stddef.h>
typedef char DLinkType;

typedef struct DLinkNode
{
  DLinkType data;
  struct DLinkNode* prev;
  struct DLinkNode* next;
}DLinkNode;

void DLinkListInit(DLinkNode** phead) ;

void DLinkListPushBack(DLinkNode* head,DLinkType value);
void DLinkListPopBack(DLinkNode* head);
void DLinkListPushFront(DLinkNode* head,DLinkType value);
void DLinkListPopFront(DLinkNode* head);
void DLinkListInsert(DLinkNode* head,DLinkNode* pos,DLinkType value);//在pos前插入;
void DLinkListInsertAfter(DLinkNode* head,DLinkNode* pos,DLinkType value);
DLinkNode* DLinkListFind(DLinkNode* head,DLinkType to_find);
void DLinkListErase(DLinkNode* head,DLinkNode* to_delete);
void DLinkListRemove(DLinkNode* head,DLinkType to_delete_value);
void DLinkListRemoveAll(DLinkNode* head,DLinkType to_delete_value);
void DLinkListDestroy(DLinkNode** phead);
size_t DLinkListSize(DLinkNode* head);
int DLinkListEmpty(DLinkNode* head);
