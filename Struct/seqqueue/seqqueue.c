#include"seqqueue.h"
void SeqQueueInit(SeqQueue* q)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    q->size = 0;
    q->head = 0;
    q->tail = 0;
    return;
}
void SeqQueueDestroy(SeqQueue* q)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    q->size = 0;
    q->head = 0;
    q->tail = 0;
    return;
}
void SeqQueuePush(SeqQueue* q,SeqQueueType value)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    if(q->size > SeqQueueMaxSize)
    {
        //队列已经满了
        return;
    }
    q->data[q->tail++] = value;
    if(q->tail > SeqQueueMaxSize)
    {
        q->tail = 0;
    }
    ++q->size;
    return;
}
void SeqQueuePop(SeqQueue* q)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    if(q->size == 0)
    {
        //空队列没法出队列
        return;
    }
    ++q->head;
    if(q->head >= SeqQueueMaxSize)
    {
        q->head = 0;
    }
    --q->size;
    return;
}
int SeqQueueFront(SeqQueue* q,SeqQueueType* value)
{
    if(q == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(q->size == 0)
    {
        return 0;
    }
    *value = q->data[q->head];
    return 1;
}

////////////////////////////////////////////////////////////////////////////
//以下为测试代码
////////////////////////////////////////////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n==========================%s===========================\n",__FUNCTION__);
void TestSeqQueue()
{
    TEST_HEADER;
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,'a');
    SeqQueuePush(&queue,'b');
    SeqQueuePush(&queue,'c');
    SeqQueuePush(&queue,'d');
    
    SeqQueueType value;
    int ret = SeqQueueFront(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected a,actual %c\n",value);
    SeqQueuePop(&queue);
    ret = SeqQueueFront(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected b,actual %c\n",value);
    SeqQueuePop(&queue);
    ret = SeqQueueFront(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected c,actual %c\n",value);
    SeqQueuePop(&queue);
    ret = SeqQueueFront(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected d,actual %c\n",value);
}
int main()
{
    TestSeqQueue();
    return 0;
}
#endif
