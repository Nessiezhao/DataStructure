#include <stdio.h>

#define SharedStackMaxSize 1000
typedef char SharedStackType;
//[0,top1)表示第一个栈
//[top2,SharedStackMaxSize)表示第二个栈
typedef struct SharedStack
{
    SharedStackType data[SharedStackMaxSize];
    size_t top1;
    size_t top2;
}SharedStack;

void SharedStackInit(SharedStack* s)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
    s->top1 = 0;
    s->top2 = SharedStackMaxSize;
    return;
}

void SharedStackPush1(SharedStack* s,SharedStackType value)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
    if(s->top1 >= s->top2)
    {
        //第一个栈已经满了
        return;
    }
    s->data[s->top1++] = value;
    return;
}

void SharedStackPush2(SharedStack* s,SharedStackType value)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
   if(s->top1 >= s->top2) 
   {
       //栈已经满了
       return;
   }
   s->data[--s->top2] = value;
   return;
}

void SharedStackPop1(SharedStack* s)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
    if(s->top1 == 0)
    {
        return;
    }
    --s->top1;
    return;
}

void SharedStackPop2(SharedStack* s)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
    if(s->top2 == SharedStackMaxSize)
    {
        return;
    }
    ++s->top2;
    return;
}

int SharedStackTop1(SharedStack* s,SharedStackType* value)
{
    if(s == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(s->top1 == 0)
    {
        return 0;
    }
    *value = s->data[s->top1 - 1];
    return 1;
}

int SharedStackTop2(SharedStack* s,SharedStackType* value)
{
    if(s == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(s->top2 == SharedStackMaxSize)
    {
        return 0;
    }
    *value = s->data[s->top2];
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////
//以下为测试代码
////////////////////////////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n=======================================%s=====================================\n",__FUNCTION__);
void TestSharedStack()
{
    TEST_HEADER;
    SharedStack stack;
    SharedStackInit(&stack);
    SharedStackPush1(&stack,'a');    
    SharedStackPush1(&stack,'b');    
    SharedStackPush1(&stack,'c');    
    SharedStackPush1(&stack,'d');    

    SharedStackType value1;
    int ret = SharedStackTop1(&stack,&value1);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected d,actual %c\n",value1);
    SharedStackPop1(&stack);
    ret = SharedStackTop1(&stack,&value1);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected c,actual %c\n",value1);
    SharedStackPop1(&stack);
    ret = SharedStackTop1(&stack,&value1);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected b,actual %c\n",value1);
    SharedStackPop1(&stack);
    ret = SharedStackTop1(&stack,&value1);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected a,actual %c\n",value1);
    SharedStackPop1(&stack);
    ret = SharedStackTop1(&stack,&value1);
    printf("ret :expected 0,actual %d\n",ret);


    TEST_HEADER;
    SharedStackPush2(&stack,'a');    
    SharedStackPush2(&stack,'b');    
    SharedStackPush2(&stack,'c');    
    SharedStackPush2(&stack,'d');    
    SharedStackType value2;
    ret = SharedStackTop2(&stack,&value2);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected d,actual %c\n",value2);
    SharedStackPop2(&stack);
    ret = SharedStackTop2(&stack,&value2);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected c,actual %c\n",value2);
    SharedStackPop2(&stack);
    ret = SharedStackTop2(&stack,&value2);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected b,actual %c\n",value2);
    SharedStackPop2(&stack);
    ret = SharedStackTop2(&stack,&value2);
    printf("ret :expected 1,actual %d\n",ret);
    printf("value :expected a,actual %c\n",value2);
    SharedStackPop2(&stack);
    ret = SharedStackTop2(&stack,&value2);
    printf("ret :expected 0,actual %d\n",ret);
}
int main()
{
    TestSharedStack();
    return 0;
}
#endif
