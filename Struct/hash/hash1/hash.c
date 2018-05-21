#include"hash.h"
#include <stdio.h>
#include<stddef.h>
size_t HashFuncDefault(KeyType key)
{
    return key % HashMaxSize;
}
void HashInit(HashTable* ht,HashFunc hash_func)
{
    ht->size = 0;
    ht->func = hash_func;
    size_t i = 0;
    for(;i < HashMaxSize;++i)
    {
        ht->data[i].stat = Empty;
    }
    return;
}
void HashDestroy(HashTable* ht)
{
    ht->size = 0;
    ht->func = NULL;
    size_t i = 0;
    for(;i < HashMaxSize;++i)
    {
        ht->data[i].stat = Empty;
    }
    return;
}
void HashInsert(HashTable* ht,KeyType key,ValType value)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    //判定hash表是否能够继续插入元素（根据负载因子）
    //假设此处我们把负载因子定义成0.8
    if(ht->size >= 0.8 * HashMaxSize)
    {
        //发现当前的hash表已经达到负载因子的上限，插入失败
        return;
    }
    //根据key来计算offset
    size_t offset = ht->func(key);
    //从offset位置开始线性的向后查找，找到第一个状态为Empty的位置进行插入
    while(1)
    {
        if(ht->data[offset].stat != Valid)//找到一个合适的位置
        {
            ht->data[offset].key = key;
            ht->data[offset].value = value;
            ht->data[offset].stat = Valid;
            ++ht->size;
            return;
        }
        //遇到key值相同的插入失败
        else if(ht->data[offset].stat == Valid && ht->data[offset].key == key)
        {
            return;
        }
        else
        {
            ++offset;
            if(offset >= HashMaxSize)
            {
                offset = 0;
            }
        }
    }
    return;
}
int HashFind(HashTable* ht,KeyType key,ValType* value)
{
    if(ht == NULL)
    {
        //非法输入
        return 0;
    }
    if(ht->size == 0)
    {
        //空的hash表
        return 0;
    }
    //根据key算出offset
    size_t offset = ht->func(key);
    //从offset开始往后进行查找，每次取到一个元素，和key进行比较
    while(1)
    {
        //如果找到key相同的元素，查找成功，并把value返回
        if(ht->data[offset].key == key && ht->data[offset].stat == Valid)
        {
            *value = ht->data[offset].value;
            return 1;
        }
        //如果是一个空位置，则查找失败
        else if(ht->data[offset].stat == Empty)
        {
            return 0;
        }
        //如果此时key不相等，就继续向后查找
        else
        {
            ++offset;
            offset = offset > HashMaxSize ? 0 : offset;
        }
    }
    return 0;
}
void HashRemove(HashTable* ht,KeyType key)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    if(ht->size == 0)
    {
        //空的hash表
        return;
    }
    //根据key计算offset
    size_t offset = ht->func(key);
    //从offset开始判定当前元素的key和要删除的key是否相等
    while(1)
    {
        if(ht->data[offset].key == key && ht->data[offset].stat == Valid)
        {
            //如果相等的话就把它标记为Deleted
            ht->data[offset].stat = Deleted;
            --ht->size;
            return;
        }
        else if(ht->data[offset].stat == Empty)
        {
            //如果当前的状态为空，那就在hash表中没找到，删除失败
            return;
        }
        else
        {
            //线性探测查找下一个元素
            ++offset;
            offset = offset > HashMaxSize ? 0 : offset;
        }
    }
    return;
}
///////////////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n==================================%s=====================================\n",__FUNCTION__);
void HashPrint(HashTable* ht,const char* msg)
{
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i < HashMaxSize;++i)
    {
        if(ht->data[i].stat == Empty)
        {
            continue;
        }
        printf("[%lu  %d : %d]\n",i,ht->data[i].key,ht->data[i].value);
    }
    return;
}
void TestInit()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    printf("size expected 0,actual %lu\n",ht.size);
    printf("func expected %p,actual %p\n",HashFuncDefault,ht.func);
}
void TestDestroy()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashDestroy(&ht);
    printf("size expected 0,actual %lu\n",ht.size);
    printf("func expected NULL,actual %p\n",ht.func);
}
void TestInsert()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,11);
    HashInsert(&ht,1002,12);
    HashPrint(&ht,"插入若干个元素");
}
void TestFind()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,11);
    HashInsert(&ht,1002,12);
    ValType value;
    int ret = HashFind(&ht,1002,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected 12,actual %d\n",value);
}
void TestRemove()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,11);
    HashInsert(&ht,1002,12);
    ValType value;
    int ret = HashFind(&ht,1002,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected 12,actual %d\n",value);

    HashRemove(&ht,1002);
    ret = HashFind(&ht,1002,&value);
    printf("ret expected 0,actual %d\n",ret);
}
int main()
{
    TestInit();
    TestDestroy();
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}
#endif
