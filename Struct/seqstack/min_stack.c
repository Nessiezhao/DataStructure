#include<stdio.h>
#include"seqstack.h"
typedef struct MinStack
{
    SeqStack stack;
}MinStack;

void MinStackInit(MinStack* min_stack)
{
    if(min_stack == NULL)
    {
        //非法输入
        return;
    }
    SeqStackInit(&min_stack->stack);
}
void MinStackPush(MinStack* min_stack,SeqStackType value)
{
    if(min_stack == NULL)    
    {
        //非法输入
        return;
    }
    SeqStackType min = value;
    SeqStackType top;
    int ret = SeqStackTop(&min_stack->stack,&top);
    if(ret != 0)
    {
        //栈非空
        min = top < value ? top : value;
    }
    //先插入value，再插入最小值，这样才能保证栈顶是最小值
    SeqStackPush(&min_stack->stack,value);
    SeqStackPush(&min_stack->stack,min);
    return;
}
void MinStackPop(MinStack* min_stack)
{
    if(min_stack == NULL)
    {
        //非法输入
        return;
    }
    if(min_stack->stack.size == 0)
    {
        return;
    }
    SeqStackPop(&min_stack->stack);
    SeqStackPop(&min_stack->stack);
    return;
}
int MinStackTop(MinStack* min_stack,SeqStackType* value)
{
    if(min_stack == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(min_stack->stack.size == 0){
        return  0;
    }
    return SeqStackTop(&min_stack->stack,value);
}
///////////////////////////////////////////////////////////////////////////////////////
//以下为测试代码
///////////////////////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n==========================%s=============================\n",__FUNCTION__);
void TestMinStack()
{
    TEST_HEADER;
    MinStack min_stack;
    MinStackInit(&min_stack);
    MinStackPush(&min_stack,'9');
    MinStackPush(&min_stack,'5');
    MinStackPush(&min_stack,'2');
    MinStackPush(&min_stack,'7');

    SeqStackType value;
    int ret = MinStackTop(&min_stack,&value);
    printf("ret expected : 1,actual %d\n",ret);
    printf("value expected : 2,actual %c\n",value);
    MinStackPop(&min_stack);
    ret = MinStackTop(&min_stack,&value);
    printf("ret expected : 1,actual %d\n",ret);
    printf("value expected : 2,actual %c\n",value);
    MinStackPop(&min_stack);
    ret = MinStackTop(&min_stack,&value);
    printf("ret expected : 1,actual %d\n",ret);
    printf("value expected : 5 actual %c\n",value);
    MinStackPop(&min_stack);
    ret = MinStackTop(&min_stack,&value);
    printf("ret expected : 1,actual %d\n",ret);
    printf("value expected : 9,actual %c\n",value);
    MinStackPop(&min_stack);
    ret = MinStackTop(&min_stack,&value);
    printf("ret expected : 0 actual %d\n",ret);
}
int main()
{
    TestMinStack();
    return 0;
}
#endif
