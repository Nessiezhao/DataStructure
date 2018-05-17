#pragma once
#include<stddef.h>
#define HeapMaxSize 1024
typedef char HeapType;

//如果a和b满足比较关系，返回1
//如果a和b不满足比较关系，返回0
//所谓的比较关系，对于小堆来说就是a<b
//对于大堆来说，就是a>b
typedef int (*Compare)(HeapType a,HeapType b);

typedef struct Heap
{
    HeapType data[HeapMaxSize];
    size_t size;
    Compare cmp;
}Heap;
//在对堆进行初始化的时候，决定堆是大堆还是小堆
void HeapInit(Heap* heap,Compare cmp);

void HeapDestroy(Heap* heap);

void HeapInsert(Heap* heap,HeapType value);
