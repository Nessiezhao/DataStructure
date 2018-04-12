#include"DLinkList.h"
#include <stdio.h>
#include<stdlib.h>
#include<stddef.h>

DLinkNode* CreateDLinkNode(DLinkType value)
{
    DLinkNode* new_node = (DLinkNode*)malloc(sizeof(DLinkNode));
    new_node->data = value;
    new_node->prev = new_node;
    new_node->next = new_node;
    return new_node;
}

void DestroyDLinkNode(DLinkNode* pos)
{
    free(pos);
}
void DLinkListInit(DLinkNode** head)
{
    if(head == NULL)
    {
     //非法输入
     return;
    }
    *head = CreateDLinkNode(0);
}
void DLinkListPushBack(DLinkNode* head,DLinkType value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    DLinkNode* tail = head->prev;
    DLinkNode* new_node = CreateDLinkNode(value);
    //head  vs  new_node
    new_node->next = head;
    head->prev =  new_node;
    //tail  vs  new_node
    tail->next = new_node;
    new_node->prev = tail;
    return;
}
void DLinkListPopBack(DLinkNode* head)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    if(head->next == head)
    {
        //空链表
        return;
    }
    DLinkNode* to_delete = head->prev;
    DLinkNode* prev = to_delete->prev;
    prev->next = head;
    head->prev = prev;
    DestroyDLinkNode(to_delete);
    return;
}
void DLinkListPushFront(DLinkNode* head,DLinkType value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    DLinkNode* new_node = CreateDLinkNode(value);
    DLinkNode* next_node = head->next;
    //head  vs  new_node
    head->next = new_node;
    new_node->prev = head;
    //new_node  vs  next_node
    new_node->next = next_node;
    next_node->prev = new_node;
    return;
}
void DLinkListPopFront(DLinkNode* head)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    if(head->next == head)
    {
        //空链表
        return;
    }
    DLinkNode* to_delete = head->next;
    DLinkNode* next_node = to_delete->next;
    head->next = next_node;
    next_node->prev = head;
    DestroyDLinkNode(to_delete);
    return;
}
void DLinkListInsert(DLinkNode* head,DLinkNode* pos,DLinkType value)//在pos前插入
{
    if(head == NULL || pos == NULL)
    {
        //非法输入
        return;
    }
    DLinkNode* new_node = CreateDLinkNode(value);
    DLinkNode* prev = pos->prev;
    //pos  vs  new_node
    pos->prev = new_node;
    new_node->next = pos;
    //prev  vs  new_node
    prev->next = new_node;
    new_node->prev = prev;
    return;
}
void DLinkListInsertAfter(DLinkNode* head,DLinkNode* pos,DLinkType value)
{
    if(head == NULL || pos == NULL)
    {
        //非法输入
        return;
    }
    DLinkNode* new_node = CreateDLinkNode(value);
    DLinkNode* next_node = pos->next;
    //new_node vs pos
    pos->next = new_node;
    new_node->prev = pos;
    //next_node  vs  next_node
    next_node->prev = new_node;
    new_node->next = next_node;
    return;
    

}
DLinkNode* DLinkListFind(DLinkNode* head,DLinkType to_find)
{
    if(head == NULL)
    {
        //非法输入
        return NULL;
    }
    DLinkNode* cur = head->next;
    for(;cur != head;cur = cur->next)
    {
        if(cur->data == to_find)
        {
            return cur;
        }
    }
    return NULL;
}
void DLinkListErase(DLinkNode* head,DLinkNode* to_delete)
{
    if(head == NULL || to_delete == NULL)
    {
        //非法输入
        return;
    }
    if(head == to_delete)
    {
        //非法输入，head指向的元素是不能被释放的，除非在销毁整个链表的时候
        return;
    }
    DLinkNode* prev_node = to_delete->prev;
    DLinkNode* next_node = to_delete->next;
    prev_node->next = next_node;
    next_node->prev = prev_node;
    DestroyDLinkNode(to_delete);
    return;
}
void DLinkListRemove(DLinkNode* head,DLinkType to_delete_value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    DLinkNode* cur = DLinkListFind(head,to_delete_value);
    if(cur == NULL)
    {
        //没有
        return;
    }
    DLinkListErase(head,cur);
}
void DLinkListRemoveAll(DLinkNode* head,DLinkType to_delete_value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    DLinkNode* cur = head->next;
    while(cur != head)
    {
       if(cur == NULL)
        {
            //没有
           return;
        }
       if(cur->data == to_delete_value)
       {
            DLinkListErase(head,cur);
       }
       cur = cur->next;
    }       
    return;
}
void DLinkListDestroy(DLinkNode** phead)
{
    if(phead == NULL)
    {
        return;
    }
    DLinkNode* cur = (*phead)->next;
    while(cur != *phead)
    {
        DLinkNode* next = cur->next;
        DestroyDLinkNode(cur);
        cur = next;
    }
    DestroyDLinkNode(*phead);
    *phead = NULL;
}
size_t DLinkListSize(DLinkNode* head)
{
    if(head == NULL)
    {
        //非法输入
        return 0;
    }
    DLinkNode* cur = head->next;
    size_t i = 0;
    for(;cur != head;cur = cur->next)
    {
        i++;
    }
    return i;
}
int DLinkListEmpty(DLinkNode* head)
{
    if(head == NULL)
    {
        //非法输入
        return 0;
    }
    if(head->next == head)
    {
        return 1;
    }
    return 2;
}
////////////////////////////////////////////////////////////////////////////////////////
//测试函数
/////////////////////////////////////////////////////////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n=============================%s================================\n",__FUNCTION__);
void DLinkListPrintChar(DLinkNode* head,const char* msg)
{
    printf("[%s]\n",msg);
    DLinkNode* cur = head->next;
    for(;cur != head;cur = cur->next )
    {
        printf("[%c|%p]",cur->data,cur);
    }
    printf("\n");
    for(cur = head->prev;cur != head;cur = cur->prev )
    {
        printf("[%c|%p]",cur->data,cur);
    }
    printf("\n");
    return;
}
void TestInit()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    printf("head expected not NULL, actual %p\n",head);
    printf("data expect 0,actual %d\n",(int)head->data);
}

void TestPushBack()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListPrintChar(head,"尾插四个元素");
}
void TestPopBack()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListPrintChar(head,"尾插四个元素");
    DLinkListPopBack(head);
    DLinkListPopBack(head);
    DLinkListPrintChar(head,"尾删两个元素");
    DLinkListPopBack(head);
    DLinkListPopBack(head);
    DLinkListPrintChar(head,"再尾删两个元素");
    DLinkListPopBack(head);
    DLinkListPrintChar(head,"尝试对空链表进行删除");
}
void TestPushFront()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkListPrintChar(head,"头插四个元素");

}
void TestPopFront()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkListPrintChar(head,"头插四个元素");
    DLinkListPopFront(head);
    DLinkListPopFront(head);
    DLinkListPrintChar(head,"头删两个元素");
    DLinkListPopFront(head);
    DLinkListPopFront(head);
    DLinkListPrintChar(head,"再头删两个元素");
    DLinkListPopFront(head);
    DLinkListPrintChar(head,"尝试对空链表进行头删");
}
void TestInsert()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListInsert(head,head->next->next,'x');
    DLinkListPrintChar(head,"在 b 元素之前插入x元素");
}
void TestInsertAfter()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListInsertAfter(head,head->next->next,'x');
    DLinkListPrintChar(head,"在 b 元素之后插入x元素");
}
void TestFind()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkNode* pos1 = DLinkListFind(head,'b');
    printf("pos1 : expected %p ,actual %p \n",head->next->next,pos1);
    DLinkNode* pos2 = DLinkListFind(head,'x');
    printf("pos2 : expected NULL, actual %p \n",pos2);
}
void TestErase()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListErase(head,head->next->next);
    DLinkListPrintChar(head,"删除链表中的 b 元素");
}
void TestRemove()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListRemove(head,'b');
    DLinkListPrintChar(head,"删除链表中的第一个 b 元素");
}
void TestRemoveAll()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'d');
    DLinkListPushBack(head,'b');
    DLinkListRemoveAll(head,'b');
    DLinkListPrintChar(head,"删除链表中所有的 b 元素");
}
void TestDestroy()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListDestroy(&head);
}
void TestSize()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'d');
    size_t i = DLinkListSize(head);
    DLinkListPrintChar(head,"打印链表中的元素");
    printf("size is :%d\n",i);
    

}
void TestEmpty()
{
    TEST_HEADER;
    DLinkNode* head1;
    DLinkListInit(&head1);
    int a = DLinkListEmpty(head1);
    DLinkListPrintChar(head1,"打印链表中的元素");
    if(a == 1)
    {
        printf("该链表为空\n");
    }
    else
    {
        printf("该链表不为空\n");
    }

    DLinkNode* head2;
    DLinkListInit(&head2);
    DLinkListPushBack(head2,'a');
    DLinkListPushBack(head2,'b');
    DLinkListPushBack(head2,'a');
    DLinkListPushBack(head2,'c');
    int b = DLinkListEmpty(head2);
    DLinkListPrintChar(head2,"打印链表中的元素");
    if(b == 1)
    {
        printf("该链表为空\n");
    }
    else
    {
        printf("该链表不为空\n");
    }
}
int main()
{
    TestInit();
    TestPushBack();
    TestPopBack();
    TestPushFront();
    TestPopFront();
    TestInsert();
    TestInsertAfter();
    TestFind();
    TestErase();
    TestRemove();
    TestRemoveAll();
    TestDestroy();
    TestSize();
    TestEmpty();
    return 0;
}
#endif
