#include <stdio.h>
#include<string.h>
#include<stdlib.h>

void Swap(int* a,int* b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}
//冒泡排序
void BubbleSort(int array[],size_t size)
{
    if(size <= 1)
    {
        return;
    }
    //[0,i)表示有序区间
    //[i,size)表示待排序区间
    size_t i = 0;
    for(;i < size ;++i)
    {
        //这里采取的是从后向前冒泡
        size_t j = size -1;
        for(;j > i;--j)
        {
            if(array[j] < array[j-1] )
            {
                Swap(&array[j],&array[j-1]);
            }
        }
    }
    return;
}
//选择排序
void SelectSort(int array[],size_t size)
{
    if(size <= 1)
    {
        return;
    }
    //[0,i)表示有序区间
    //[i,size)表示待排序区间
    size_t i = 0;
    for(; i < size ;++i)
    {
        size_t j = i + 1;
        for(; j < size;++j)
        {
            if(array[i] > array[j])
            {
                Swap(&array[i],&array[j]);
            }
        }
    }
    return;
}
//插入排序
void InsertSort(int array[],size_t size)
{
    if(size <= 1)
    {
        return;
    }
    //[0,i)表示有序区间
    //[i,size)表示待排序区间
    //插入排序是把前面的有序区间当做一个线性表
    //然后把 i_value 的值插入到线性表中合适的位置上
    size_t i = 1;
    for(; i < size;++i)
    {
        //此时存起来的意义是为了后面的搬运
        //一旦array[i]元素被单独保存起来了
        //array[i]数值就可以被修改了
        int i_value = array[i];
        //此时cur是辅助我们进行搬运的下标
        //从后向前遍历，找到合适的位置放 i_value 的位置
        size_t cur = i;
        for(;cur > 0;--cur)
        {
            //此处我们的初始情况就是拿线性表的最后一个元素和 i_value 比较
            //因此 array[cur-1]这里的 cur 取决于 cur 的初始位置
            if(array[cur-1] > i_value)
            {
                //进行搬运
                array[cur] = array[cur-1];
            }
            else
            {
                //说明已经找到了合适的位置
                break;
            }
        }
        //然后把i位置的元素插入到线性表的合适的位置上
        array[cur] = i_value;
    }
    return;
}
//方法一：
//把新元素放到数组的末尾，进行上浮式的调整（从前往后遍历）
//方法二：
//采用下沉式的调整从后往前遍历
//起始位置就是堆的从后往前遍历的第一个非叶子节点
void AdjustDown(int array[],size_t size,size_t index)
{
    size_t parent = index;
    size_t child = 2 * index + 1 ;
    while(child < size)
    {
        if(child + 1 < size && array[child] < array[child+1])
        {
            child = child + 1;
        }
        if(array[parent] < array[child])
        {
            Swap(&array[parent],&array[child]);
        }
        parent = child;
        child = 2 * parent + 1;
    }
    return;
}
void HeapCreate(int array[],size_t size)
{
    if(size <= 1)
    {
        return;
    }
    size_t i = (size -1 -1) / 2;
    for(;i > 0;--i)
    {
        AdjustDown(array,size,i);
    }
    AdjustDown(array,size,0);
    return;
}
void HeapPop(int array,size_t heap_size)
{
    if(heap_size <= 1)
    {
        return;
    }
    Swap(&array[0],&array[heap_size-1]);
    AdjustDown(array,heap_size - 1,0);
}
void HeapSort(int array[],size_t size)
{
    if(size <= 1)
    {
        return;
    }
    //1.基于数组建立一个堆（如果是升序，就建立大堆）
    HeapCreate(array,size);
    //2.循环的删除堆顶元素，将所有的元素都删除完毕，排序完成
    size_t i = 0;
    for(;i < size;++i)
    {
        //第二个参数表示数组中哪部分区间是符合堆的规则
        //第一个删除之前，[0,size)都是堆
        //第二次删除之前，[0,size-1)都是堆
        //第三次删除之前，[0,size-2)都是堆
        HeapPop(array,size-i);
    }
    return;
}
int main()
{
    return 0;
}
