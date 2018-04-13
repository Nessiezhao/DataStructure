#include"seqstack.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
void SeqStackInit(SeqStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    stack->size = 0;
    stack->capacity = 1000;
    stack->data = (SeqStackType*)malloc(stack->capacity*sizeof(SeqStackType));
}
void SeqStackDestroy(SeqStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    free(stack->data);
    stack->size = 0;
    stack->capacity = 0;
}
void SeqStackResize(SeqStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size < stack->capacity)
    {
        return;
    }
    stack->capacity = stack->capacity * 2 + 1;
    SeqStackType* new_ptr = (SeqStackType*)malloc(stack->capacity * sizeof(SeqStackType));
    size_t i = 0;
    for(;i <stack->size;++i )
    {
        new_ptr[i] = stack->data[i];
    }
    free(stack->data);
    stack->data = new_ptr;
    return;
}
void SeqStackPush(SeqStack* stack,SeqStackType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size > stack->capacity)
    {
        SeqStackResize(stack);
    }
    stack->data[stack->size++] = value;
    return;
}
void SeqStackPop(SeqStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size == 0)
    {
        return;
    }
    --stack->size;
    return;
}
//返回两个信息：执行成功失败，栈顶元素的值是多少
int SeqStackTop(SeqStack* stack,SeqStackType* value)
{
    if(stack == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(stack->size == 0)
    {
        //空栈
        return 0;
    }
    *value = stack->data[stack->size-1];
    return 1;
}
///////////////////////////////////////////////////////////////
//以下为测试代码
///////////////////////////////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n==============================%s====================================\n",__FUNCTION__);
void SeqStackPrintChar(SeqStack* stack,const char* msg)
{
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i < stack->size;++i)
    {
       printf("[%c] ",stack->data[i]) ;
    }
    printf("\n");
    return;
}
void TestInit()
{
    TEST_HEADER;
    SeqStack stack;
    SeqStackInit(&stack);
    printf("size expected : 0,actual %lu\n",stack.size);
    printf("capacity expected : 1000,actual %lu\n" ,stack.capacity);
}
void TestDestroy()
{
    TEST_HEADER;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackDestroy(&stack);
    printf("size expected : 0,actual %lu\n",stack.size);
    printf("capacity expected : 0,actual %lu\n" ,stack.capacity);
}
void TestPush()
{
    TEST_HEADER;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');
    SeqStackPrintChar(&stack,"入栈四个元素");
}
void TestPop()
{
    TEST_HEADER;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');
    SeqStackPop(&stack);
    SeqStackPrintChar(&stack,"出栈一个元素");
    SeqStackPop(&stack);
    SeqStackPop(&stack);
    SeqStackPrintChar(&stack,"出栈两个元素");
    SeqStackPop(&stack);
    SeqStackPop(&stack);
    SeqStackPrintChar(&stack,"出栈两个元素");
}
void TestTop()
{
    TEST_HEADER;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');
    SeqStackPrintChar(&stack,"入栈四个元素");

    SeqStackType value;
    int ret = SeqStackTop(&stack,&value);
    printf("ret expected : 1，actual %d\n",ret);
    printf("value expected : d,actual %c\n",value);

    SeqStackPop(&stack);
    SeqStackPop(&stack);
    ret = SeqStackTop(&stack,&value);
    printf("ret expected : 1，actual %d\n",ret);
    printf("value expected : b,actual %c\n",value);

    SeqStackPop(&stack);
    SeqStackPop(&stack);
    ret = SeqStackTop(&stack,&value);
    printf("ret expected : 0，actual %d\n",ret);
}
int main()
{
    TestInit();
    TestDestroy();
    TestPush();
    TestPop();
    TestTop();
    return 0;
}

#endif
