#include <stdio.h>
#include"seqqueue.h"

typedef struct StackBy2Queue
{
    SeqQueue queue1;
    SeqQueue queue2;
}StackBy2Queue;

void StackBy2QueueInit(StackBy2Queue* s)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
    SeqQueueInit(&s->queue1);
    SeqQueueInit(&s->queue2);
    return;
}
void StackBy2QueuePush(StackBy2Queue* s,SeqQueueType value)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
    //取两个队列中非空的插入
    SeqQueue* input = s->queue1.size != 0 ? &s->queue1 : &s->queue2;
    SeqQueuePush(input,value);
    return;
}
void StackBy2QueuePop(StackBy2Queue* s)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
    if(s->queue1.size == 0 && s->queue2.size == 0)
    {
        //说明是空栈
        return;
    }
    //要把from中的元素倒腾到to中
    //并且一直倒腾到from中只剩一个元素
    SeqQueue* from = NULL;
    SeqQueue* to = NULL;
    if(s->queue1.size > 0)
    {
        from = &s->queue1;
        to = &s->queue2;
    }
    else
    {
        from = &s->queue2;
        to = &s->queue1;
    }
    while(1)
    {
        if(from->size == 1)
        {
            //from中只剩下一个元素
            break;
        }
        SeqQueueType value;
        SeqQueueFront(from,&value);
        SeqQueuePop(from);
        SeqQueuePush(to,value);
    }
    SeqQueuePop(from);
    return;
}
int StackBy2QueueTop(StackBy2Queue* s,SeqQueueType* value)
{
    if(s == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    //要把from中的元素倒腾到to中
    //并且一直倒腾到from中只剩一个元素
    SeqQueue* from = NULL;
    SeqQueue* to = NULL;
    if(s->queue1.size > 0)
    {
        from = &s->queue1;
        to = &s->queue2;
    }
    else
    {
        from = &s->queue2;
        to = &s->queue1;
    }
    while(1)
    {
        if(from->size == 0) {
            //已经要停止倒腾了，此时的from的对首元素就是栈顶元素
            break;
        }
        SeqQueueFront(from,value);
        SeqQueuePop(from);
        SeqQueuePush(to,*value);
    }
    SeqQueueFront(from,value);
}
////////////////////////////////////////////////////////////////////////////////
//以下为测试代码
////////////////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n===================================%s======================================\n",__FUNCTION__);
void TestStackBy2Queue()
{
    TEST_HEADER;
    StackBy2Queue stack;
    StackBy2QueueInit(&stack);
    StackBy2QueuePush(&stack,'a');
    StackBy2QueuePush(&stack,'b');
    StackBy2QueuePush(&stack,'c');
    StackBy2QueuePush(&stack,'d');

    SeqQueueType value;
    int ret = StackBy2QueueTop(&stack,&value);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected d,actual %c\n",value);
    StackBy2QueuePop(&stack);
    ret = StackBy2QueueTop(&stack,&value);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected c,actual %c\n",value);
    StackBy2QueuePop(&stack);
    ret = StackBy2QueueTop(&stack,&value);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected b,actual %c\n",value);
    StackBy2QueuePop(&stack);
    ret = StackBy2QueueTop(&stack,&value);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected a,actual %c\n",value);
    StackBy2QueuePop(&stack);
   ret = StackBy2QueueTop(&stack,&value);
   printf("ret :expected 0,actual %d\n",ret);
}
int main()
{
    TestStackBy2Queue();
    return 0;
}
#endif
