#include <stdio.h>
#include"seqstack.h"

typedef struct QueueBy2Stack
{
    //input 用于入队列场景
    SeqStack input;
    //output 用于出队列场景
    SeqStack output;
}QueueBy2Stack;

void QueueBy2StackInit(QueueBy2Stack* q)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    SeqStackInit(&q->input);
    SeqStackInit(&q->output);
}

void QueueBy2StackPush(QueueBy2Stack* q,SeqStackType value)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    //先把output中的元素都倒腾到input中
    while(1)
    {
        SeqStackType top;
        int ret = SeqStackTop(&q->output,&top);
        if(ret == 0)
        {
            break;
        }
        SeqStackPop(&q->output);
        SeqStackPush(&q->input,top);
    }
    //再把value入队列
    SeqStackPush(&q->input,value);
    return;
}
void QueueBy2StackPop(QueueBy2Stack* q)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    //把input中的元素都倒腾到output中
    while(1)
    {
        SeqStackType top;
        int ret = SeqStackTop(&q->input,&top);
        if(ret == 0)
        {
            break;
        }
        SeqStackPop(&q->input);
        SeqStackPush(&q->output,top);
    }
    SeqStackPop(&q->output);
    return;
}
int QueueBy2StackFront(QueueBy2Stack* q,SeqStackType* value)
{
    if(q == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    while(1)
    {
        SeqStackType top;
        int ret = SeqStackTop(&q->input,&top);
        if(ret == 0)
        {
            break;
        }
        SeqStackPop(&q->input);
        SeqStackPush(&q->output,top);
    }
    return SeqStackTop(&q->output,value);
}
///////////////////////////////////////////////////////////////////////////////////////
//以下为测试代码
///////////////////////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n===================================%s=====================================\n",__FUNCTION__);
void TestQueueBy2Stack()
{
    TEST_HEADER;
    QueueBy2Stack queue;
    QueueBy2StackInit(&queue);
    QueueBy2StackPush(&queue,'a');
    QueueBy2StackPush(&queue,'b');
    QueueBy2StackPush(&queue,'c');
    QueueBy2StackPush(&queue,'d');

    SeqStackType value;
    int ret = QueueBy2StackFront(&queue,&value);
    printf("ret :expected 1 ,actual %d\n",ret);
    printf("value :expected a ,actual %c\n",value);

    QueueBy2StackPop(&queue);
    ret = QueueBy2StackFront(&queue,&value);
    printf("ret :expected 1 ,actual %d\n",ret);
    printf("value :expected b ,actual %c\n",value);
    
    QueueBy2StackPop(&queue);
    ret = QueueBy2StackFront(&queue,&value);
    printf("ret :expected 1 ,actual %d\n",ret);
    printf("value :expected c ,actual %c\n",value);

    QueueBy2StackPop(&queue);
    ret = QueueBy2StackFront(&queue,&value);
    printf("ret :expected 1 ,actual %d\n",ret);
    printf("value :expected d ,actual %c\n",value);
    
    QueueBy2StackPop(&queue);
    ret = QueueBy2StackFront(&queue,&value);
    printf("ret :expected 0 ,actual %d\n",ret);

}
int main()
{
    TestQueueBy2Stack();
    return 0;
}
#endif
