#pragma once

#include<stddef.h>

typedef char SeqStackType;

typedef struct SeqStack
{
    SeqStackType* data;
    size_t size;
    size_t capacity;//max_size 的代替品，data这段内存中能容纳的元素个数
}SeqStack;

void SeqStackInit(SeqStack* stack);
void SeqStackDestroy(SeqStack* stack);
void SeqStackResize(SeqStack* stack);
void SeqStackPush(SeqStack* stack,SeqStackType value);
void SeqStackPop(SeqStack* stack);
//返回两个信息：执行成功失败，栈顶元素的值是多少
int SeqStackTop(SeqStack* stack,SeqStackType* value);
