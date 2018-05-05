#include"seqstack.h"

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

#ifdef FOR_MAZE
//#include<stdio.h>
//#include"seqstack.h"
//此函数仅用于迷宫问题，用来调试
//通常意义下，栈是不允许遍历的
//但是如果进行调试或者测试，就不一样了
//因此再这里虽然函数进行遍历了，但是仅用于调试
//之所以写这个函数遍历栈，是为了能够从入口到出口的顺序来打印栈的内容
void SeqStackDebugPrint(SeqStack* stack,const char* msg)
{
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i < stack->size ; ++i)
    {
        printf("(%d,%d)\n",stack->data[i].row,stack->data[i].col);
    }
    printf("\n");
}
void SeqStackAssgin(SeqStack* from,SeqStack* to)
{
    //采用下面的方法保证to里面的内存能够足够容纳from中的元素
    //1.释放to中的原有内存
    SeqStackDestroy(to);
    //2.根据from元素的个数，确定内存申请内存的大小，给to重新申请一个足够的内存
    to->size = from->size;
    to->capacity = from->capacity;
    to->data = (SeqStackType*)malloc(to->capacity * sizeof(SeqStackType));
    //3.进行数据拷贝
    size_t i = 0;
    for(;i < from->size ; ++i)
    {
        to->data[i] = from->data[i];
    }
    return;
}
#endif
///////////////////////////////////////////////////////////////
//以下为测试代码
///////////////////////////////////////////////////////////////
#if 0
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
