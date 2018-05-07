#pragma once

#include <stdio.h>
#include <stdlib.h>
//#define FOR_MAZE
#define FOR_TREE


#ifdef FOR_TREE
struct TreeNode;
typedef struct TreeNode* SeqStackType;
#else
typedef char SeqStackType;
#endif

typedef struct SeqStack
{
    SeqStackType* data;
    size_t size;
    size_t capacity;//max_size 的代替品，data这段内存中能容纳的元素个数
}SeqStack;
//typedef Point SeqStackType;

void SeqStackDebugPrint(SeqStack* stack,const char* msg);
void SeqStackAssgin(SeqStack* cur_path,SeqStack* short_path);

void SeqStackInit(SeqStack* stack);
void SeqStackDestroy(SeqStack* stack);
void SeqStackResize(SeqStack* stack);
void SeqStackPush(SeqStack* stack,SeqStackType value);
void SeqStackPop(SeqStack* stack);
//返回两个信息：执行成功失败，栈顶元素的值是多少
int SeqStackTop(SeqStack* stack,SeqStackType* value);

