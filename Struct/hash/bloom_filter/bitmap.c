#include"bitmap.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
uint64_t Getsize(uint64_t capacity)
{
    uint64_t size = capacity / (sizeof(BitmapType)*8)+1;
    return size;
}
void BitmapInit(Bitmap* bm,uint64_t capacity)
{
    if(bm == NULL)
    {
        return;
    }
    //capacity表示该位图能保存的最大的数
    //比如 capacity = 100，2个元素
    //比如 capacity = 200，4个元素
    //比如 capacity = 300，5个元素
    //比如 capacity = N，N/（sizeof(uint64_t) * 8）+ 1
    bm->capacity = capacity;
    //size 是我们申请内存时对应的数组元素个数
    uint64_t size = Getsize(capacity);
    bm->data = (BitmapType*)malloc(sizeof(BitmapType)*size);
    memset(bm->data,0,sizeof(BitmapType)*size);
    return;
}

void BitmapDestroy(Bitmap* bm)
{
    if(bm == NULL)
    {
        return;
    }
    bm->capacity = 0;
    free(bm->data);
    return;
}
void GetOffset(uint64_t index,uint64_t* n,uint64_t* offset)
{
    *n = index / (sizeof(BitmapType)*8);
    *offset = index % (sizeof(BitmapType)*8);
    return;
}
void BitmapSet(Bitmap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        return;
    }
    uint64_t n,offset;
    GetOffset(index,&n,&offset);
    bm->data[n] |= (0x1ul << offset);
    return;
}
void BitmapUnset(Bitmap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        return;
    }
    uint64_t n,offset;
    GetOffset(index,&n,&offset);
    bm->data[n] &= ~(0x1ul << offset);
    return;

}

void BitmapFill(Bitmap* bm)
{
    if(bm == NULL)
    {
        return;
    }
    uint64_t size = Getsize(bm->capacity);
    memset(bm->data,0xff,(sizeof(BitmapType)*size));
    return;
}

void BitmapClear(Bitmap* bm)
{
    if(bm == NULL)
    {
        return;
    }
    uint64_t size = Getsize(bm->capacity);
    memset(bm->data,0x0,(sizeof(BitmapType)*size));
    return;
}

int BitmapTest(Bitmap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        //非法输入
        return 0;
    }
    uint64_t n,offset;
    GetOffset(index,&n,&offset);
    uint64_t ret = bm->data[n] & (0x1ul << offset);
    return ret > 0 ? 1 : 0;
}
///////////////////////////////////////////////////////////////
//以下为测试代码
///////////////////////////////////////////////////////////////
#if 0
#define TEST_HEADER printf("\n============================%s===============================\n",__FUNCTION__);
void TestSet()
{
    TEST_HEADER;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapSet(&bm,50);
    int ret = BitmapTest(&bm,50);
    printf("ret expected 1,actual %d\n",ret);
    ret = BitmapTest(&bm,20);
    printf("ret expected 0,actual %d\n",ret);
}
void TestUnset()
{
    TEST_HEADER;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapSet(&bm,50);
    int ret = BitmapTest(&bm,50);
    printf("ret expected 1,actual %d\n",ret);
    BitmapUnset(&bm,50);
    ret = BitmapTest(&bm,50);
    printf("ret expected 0,actual %d\n",ret);
}
void TestFill()
{
    TEST_HEADER;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapFill(&bm);
    int ret = BitmapTest(&bm,50);
    printf("ret expected 1,actual %d\n",ret);
    ret = BitmapTest(&bm,0);
    printf("ret expected 1,actual %d\n",ret);
    ret = BitmapTest(&bm,99);
    printf("ret expected 1,actual %d\n",ret);
}
int main()
{
    TestSet();
    TestUnset();
    TestFill();
    return 0;
}
#endif
