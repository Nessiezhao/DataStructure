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
//堆排序
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
void HeapPop(int array[],size_t heap_size)
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
//希尔排序
void ShellSort(int array[],int64_t size)
{
    if(size <= 1)
    {
        return;
    }
    //此时我们使用希尔排序
    int64_t gap = size / 2;
    //第一重循环，生成步长序列
    for(;gap > 0;gap /= 2)
    {
        //第二重循环，进行插入排序
        //此循环执行的顺序，相当于
        //先处理第一组的第一个数据
        //再处理第二组的第一个数据
        //再处理第三组的第一个数据
        //...
        //再处理第一组的第二个数据
        int64_t i = gap;//此处相当于插入排序中的 i = 1
        for(;i < size;++i)
        {
            //此时i_value 就是待插入元素
            int i_value = array[i];
            //第三重循环，线性表的查找和搬运
            int64_t cur = i;
            //此处 cur -= gap 就是在找同组元素中的上一个元素
            for(;cur >= gap; cur -= gap)
            {
                if(array[cur-gap] > i_value)
                {
                    //此时进行搬运
                    array[cur] = array[cur-gap];
                }
                else
                {
                    //找到了
                    break;
                }
            }
            array[cur] = i_value;
        }
    }
    return;
}
//归并排序
void _MergeArray(int array[],int64_t beg,int64_t mid,int64_t end,int* tmp)
{
    int64_t cur1 = beg;
    int64_t cur2 = mid;
    int64_t tmp_index = beg;
    while(cur1 < mid && cur2 < end)
    {
        if(array[cur1] < array[cur2])
        {
            tmp[tmp_index++] = array[cur1++];
        }
        else 
        {
            tmp[tmp_index++] = array[cur2++];
        }
    }
    while(cur1 < mid)
    {
        tmp[tmp_index++] = array[cur1++];
    }
    while(cur2 < end)
    {
        tmp[tmp_index++] = array[cur2++];
    }
    memcpy(array+beg,tmp+beg,sizeof(int) * (end - beg));
    return;
}
void _MergeSort(int array[],int64_t beg,int64_t end,int* tmp )
{
    if(end - beg <= 1)
    {
        //要么没元素，要么一个元素，要么是非法区间
        return;
    }
    int64_t mid = beg + (end - beg) / 2;
    //此时有了两个区间
    //[beg,mid)
    //[mid,end) 
    _MergeSort(array,beg,mid,tmp);
    _MergeSort(array,mid,end,tmp);
    _MergeArray(array,beg,mid,end,tmp);
}
void MergeSort(int array[],size_t size)
{
    //此时我们创建一个临时空间用来合并元素
    int* tmp = (int*)malloc(sizeof(int) * size);
    _MergeSort(array,0,size,tmp);
    free(tmp);
    return;
}
int main()
{
    int array[] = {5,4,6,7,8,2,1,9};
    int i = 0;
    int size = sizeof(array)/sizeof(array[0]);
    ShellSort(array,sizeof(array)/sizeof(array[0]));
    for(i = 0;i <size;i++)
    {
        printf("%d  ",array[i]);
    }
    printf("\n");
    int array1[] = {5,4,6,7,8,2,1,9};
    HeapSort(array1,sizeof(array1)/sizeof(array1[0]));
    for(i = 0;i <size;i++)
    {
        printf("%d  ",array1[i]);
    }
    printf("\n");
    int array2[] = {5,3,6,7,8,2,1,9};
    InsertSort(array2,sizeof(array2)/sizeof(array2[0]));
    for(i = 0;i <size;i++)
    {
        printf("%d  ",array2[i]);
    }
    printf("\n");
    int array3[] = {5,3,6,7,8,2,1,9};
    BubbleSort(array3,sizeof(array3)/sizeof(array3[0]));
    for(i = 0;i <size;i++)
    {
        printf("%d  ",array3[i]);
    }
    printf("\n");
    int array4[] = {5,3,6,7,8,2,1,9};
    SelectSort(array4,sizeof(array4)/sizeof(array4[0]));
    for(i = 0;i <size;i++)
    {
        printf("%d  ",array4[i]);
    }
    printf("\n");
    int array5[] = {5,4,6,7,8,2,1,9};
    MergeSort(array5,sizeof(array5)/sizeof(array[0]));
    for(i = 0;i < size;++i)
    {
        printf("%d  ",array5[i]);
    }
    printf("\n");
    return 0;
}
