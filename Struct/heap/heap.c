#include <stdio.h>
#include<string.h>
#include"heap.h"

int Less(HeapType a,HeapType b)
{
    return a < b ? 1 : 0;
}

int Greater(HeapType a,HeapType b)
{
    return a > b ? 1 : 0;
}
void HeapInit(Heap* heap,Compare cmp)
{
    if(heap == NULL)
    {
        return;
    }
    heap->size = 0;
    heap->cmp = cmp;
    return;
}
void HeapDestroy(Heap* heap)
{
    if(heap == NULL)
    {
        return;
    }
    heap->size = 0;
    heap->cmp = NULL;
    return;
}
void Swap(HeapType* a,HeapType* b)
{
    HeapType tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void AdjustUp(Heap* heap,size_t index)
{
    if(heap == NULL)
    {
        return;
    }
    size_t child = index;
    size_t parent = (child -1)/2;
    while(child > 0)
    {
        if(!heap->cmp(heap->data[parent],heap->data[child]))
        {
            Swap(&heap->data[parent],&heap->data[child]);
        }
        else
        {
            break;
        }
        child = parent;
        parent = (child -1)/2;
    }
    return;
}
void HeapInsert(Heap* heap,HeapType value)
{
    if(heap == NULL)
    {
        return;
    }
    if(heap->size >= HeapMaxSize)
    {
        return;
    }
    heap->data[heap->size++] = value;
    AdjustUp(heap,heap->size - 1);
    return;
}
int HeapRoot(Heap* heap,HeapType* value)
{
    if(heap == NULL || value == NULL)
    {
        return 0;
    }
    *value = heap->data[0];
    return 1;
}
void AdjustDown(Heap* heap,size_t index)
{
    if(heap == NULL)
    {
        return;
    }
    if(heap->size == 0)
    {
        return;
    }
    size_t parent = index;
    size_t child = 2 * index + 1;
    while(child < heap->size)
    {
        if(child+1 < heap->size && heap->cmp(heap->data[child+1],heap->data[child]))
        {
            child = child + 1;
        }
        if(heap->cmp(heap->data[child],heap->data[parent]))
        {
            Swap(&heap->data[parent],&heap->data[child]);
        }
        parent = child;
        child = 2 * parent + 1;
    }
}
void HeapErase(Heap* heap)
{
    if(heap == NULL)
    {
        return;
    }
    if(heap->size == 0)
    {
        return;
    }
    Swap(&heap->data[0],&heap->data[heap->size -1]);
    --heap->size;
    AdjustDown(heap,0);
    return;
}
void HeapCreate(Heap* heap,HeapType array[],size_t size)
{
    if(heap == NULL)
    {
        return;
    }
    size_t i = 0;
    for(;i < size;++i)
    {
        HeapInsert(heap,array[i]);
    }
    return;
}
void HeapSort(HeapType array[],size_t size)
{
    Heap heap;
    HeapInit(&heap,Greater);
    HeapCreate(&heap,array,size);
    while(heap.size > 0)
    {
        HeapErase(&heap);
    }
    memcpy(array,heap.data,size * sizeof(HeapType));
    return;
}
///////////////////////////////////////////////////////////////
//以下为测试代码
///////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n==========================%s=================================\n",__FUNCTION__);
void TestInit()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    printf("size expected 0,actual %lu\n",heap.size);
    printf("cmp expected %p,actual %p\n",Greater,heap.cmp);
}
void TestDestroy()
{
    TEST_HEADER;
    Heap heap;
    HeapDestroy(&heap);
    printf("size expected 0,actual %lu\n",heap.size);
    printf("cmp expected NULL,actual %p\n",heap.cmp);
}
void HeapPrintChar(Heap* heap,const char* msg)
{
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i < heap->size; ++i)
    {
        printf("[%c | %lu] ",heap->data[i],i);
    }
    printf("\n");
}
void TestInsert()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapPrintChar(&heap,"给堆中插入6个元素");
}
void TestRoot()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapType value;
    int ret = HeapRoot(&heap,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected f,actual %c\n",value);
}
void TestErase()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapErase(&heap);
    HeapPrintChar(&heap,"删除堆顶元素");
}
void TestCreate()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapType array[] = {'d','e','c','a','b'};
    HeapCreate(&heap,array,sizeof(array)/sizeof(array[0]));
    HeapPrintChar(&heap,"创建一个堆");
}
void TestSort()
{
    TEST_HEADER;
    HeapType array[] = {'d','e','c','a','b'};
    HeapSort(array,sizeof(array)/sizeof(array[0]));
    size_t i = 0;
    for(;i < sizeof(array);++i)
    {
        printf("[%c] ",array[i]);
    }
    printf("\n");
}
int main()
{
    TestInit();
    TestDestroy();
    TestInsert();
    TestRoot();
    TestErase();
    TestCreate();
    TestSort();
    return 0;
}
#endif
