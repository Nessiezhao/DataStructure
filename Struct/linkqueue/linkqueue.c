#include"linkqueue.h"
#include <stdio.h>
#include<stdlib.h>
void LinkQueueInit(LinkQueue* q)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    q->head = NULL;
    q->tail = NULL;
    return;
}
void LinkQueueDestroy(LinkQueue* q)//销毁队列
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    LinkNode* cur = q->head;
    for(;cur!= NULL;cur=cur->next)
    {
        free(cur);
    }
    q->head = q->tail = NULL;
    return;
}
void DestroyLinkNode(LinkNode* to_delete)
{
    if(to_delete == NULL)
    {
        return;
    }
    free(to_delete);
    to_delete = NULL;
    return;
}
LinkNode* CreateLinkNode(LinkType value)
{
    LinkNode* tmp = (LinkNode*)malloc(sizeof(LinkNode));
    if(!tmp)
    {
        printf("CreateLinkNode error!\n");
        return NULL;
    }
    tmp->data = value;
    tmp->next = NULL;
    return tmp;
}
void LinkQueuePush(LinkQueue* q,LinkType value)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    LinkNode* temp = CreateLinkNode(value);
    if(q->head == NULL)
    {
        q->head  = temp;
        q->tail = temp;
        return;
    }
    q->tail->next = temp;
    q->tail = temp;
    return;
}
void LinkQueuePop(LinkQueue* q)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    LinkNode* to_delete = q->head;
    q->head = q->head->next;
    DestroyLinkNode(to_delete);
    return;
}
int LinkQueueFront(LinkQueue* q,LinkType* value)
{
    if(q == NULL )
    {
        //非法输入
        return 0;
    }
    *value = q->head->data;
    return 1;
}
//////////////////////////////////////////////////////////////////////////
//以下为测试代码
/////////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n======================%s========================\n",__FUNCTION__);
void LinkQueuePrintChar(LinkQueue* q,const char* msg)
{
    printf("[%s]\n",msg);
    LinkNode* cur = q->head;
    for(;cur!= NULL;cur=cur->next)
    {
        printf("[%c][%p]<- ",cur->data,cur);
    }
    printf("NULL\n");
    printf("\n");
    
}
void TestQueue()
{
    TEST_HEADER;
    LinkQueue queue;
    LinkQueueInit(&queue);
    LinkQueuePush(&queue,'a');
    LinkQueuePush(&queue,'b');
    LinkQueuePush(&queue,'c');
    LinkQueuePush(&queue,'d');
    LinkQueuePrintChar(&queue,"打印队列");

    LinkType value;
    int ret = LinkQueueFront(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected a,actual %c\n",value);

    LinkQueuePop(&queue);
    ret = LinkQueueFront(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected b,actual %c\n",value);

    LinkQueuePop(&queue);
    ret = LinkQueueFront(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected c,actual %c\n",value);

    LinkQueuePop(&queue);
    ret = LinkQueueFront(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected d,actual %c\n",value);

    LinkQueue queue1;
    LinkQueueInit(&queue1);
    LinkQueuePush(&queue1,'a');
    LinkQueuePush(&queue1,'b');
    LinkQueuePush(&queue1,'c');
    LinkQueuePush(&queue1,'d');
    LinkQueuePrintChar(&queue1,"打印队列");
    
    LinkQueueDestroy(&queue1);
    LinkQueuePrintChar(&queue1,"打印队列");
}
int main()
{
    TestQueue();
    return 0;
}
#endif
