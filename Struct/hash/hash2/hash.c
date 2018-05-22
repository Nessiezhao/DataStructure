#include"hash.h"
#include <stdio.h>
#include<stdlib.h>
#include<stddef.h>

HashElem* CreateElem(KeyType key,ValType value)
{
    HashElem* new_node = (HashElem*)malloc(sizeof(HashElem));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}
void DestroyElem(HashElem* node)
{
    free(node);
    return;
}
size_t HashFuncDefault(KeyType key)
{
    return key % HashMaxSize;
}
void HashInit(HashTable* ht,HashFunc hash_func)
{
    if(ht == NULL)
    {
        return;
    }
    ht->size = 0;
    ht->func = hash_func;
    size_t i = 0;
    for(;i < HashMaxSize ;++i)
    {
        ht->data[i] = NULL;
    }
    return;
}

void HashDestroy(HashTable* ht)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    ht->size = 0;
    ht->func = NULL;
    size_t i = 0;
    //遍历所有的链表然后进行释放
    for(;i < HashMaxSize;++i)
    {
        HashElem* cur = ht->data[i];
        while(cur != NULL)
        {
            HashElem* next = cur->next;
            DestroyElem(cur);
            cur = next;
        }
    }
    return;
}
HashElem* HashBucketFind(HashElem* head,KeyType to_find)
{
    HashElem* cur = head;
    for(;cur != NULL;cur = cur->next)
    {
        if(cur->key == to_find)
        {
            break;
        }
    }
    return cur == NULL ? NULL : cur;
}
void HashInsert(HashTable* ht,KeyType key,ValType value)
{
    if(ht == NULL)
    {
        return;
    }
    //根据key算出offset
    size_t offset = ht->func(key);
    //在offset对应的链表中查找看当前的key是否存在
    HashElem* ret = HashBucketFind(ht->data[offset],key);
    if(ret != NULL)
    {
        //如果返回值不为空，就说明已经存在当前key
        //如果存在就认为插入失败
        return;
    }
    //如果不存在就采用头插的办法
    HashElem* new_node = CreateElem(key,value);
    new_node->next = ht->data[offset];
    ht->data[offset] = new_node;
    ++ht->size;
    return;
}
int HashFind(HashTable* ht,KeyType key,ValType* value)
{
    if(ht == NULL || value == NULL)
    {
        return 0;
    }
    //根据key算出offset
    size_t offset = ht->func(key);
    HashElem* ret = HashBucketFind(ht->data[offset],key);
    if(ret == NULL )
    {
        return 0;
    }
    *value = ret->value;
    return 1;
}
int HashBucketFindEx(HashElem* head,KeyType to_find,HashElem** pre_node,HashElem** cur_node)
{
    HashElem* pre = NULL;
    HashElem* cur = head;
    for(;cur != NULL;pre = cur,cur = cur->next)
    {
        if(cur->key == to_find)
        {
            break;
        }
    }
    if(cur == NULL)
    {
        return 0;
    }
    *pre_node = pre;
    *cur_node = cur;
    return 1;
}
void HashRemove(HashTable* ht,KeyType key)
{
    if(ht == NULL)
    {
        return;
    }
    if(ht->size == 0)
    {
        return;
    }
    //根据key算出offset
    size_t offset = ht->func(key);
    //通过offset找到对应的链表
    //在链表中找到指定的元素，并进行删除
    HashElem* pre =NULL;
    HashElem* cur = NULL;
    int ret = HashBucketFindEx(ht->data[offset],key,&pre,&cur);
    if(ret == 0)
    {
        //没找到，删除失败
        return;
    }
    if(pre == NULL)
    {
        //要删除的元素是链表的头结点
        ht->data[offset] = cur->next;
    }
    else
    {
        //要删除的点不是链表的头结点
        pre->next = cur->next;
    }
    DestroyElem(cur);
    --ht->size;
    return;
}
///////////////////////////////////////////////////////////////////
//以下为测试代码
///////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n================================%s===============================\n",__FUNCTION__);
void TestInit()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    printf("size expected 0,actual %lu\n",ht.size);
    printf("func expected %p,actual %p\n",HashFuncDefault,ht.func);
}
void HashPrint(HashTable* ht,const char* msg)
{
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i < HashMaxSize ;++i)
    {
        if(ht->data[i] == NULL)
        {
            continue;
        }
        printf("i = %lu\n",i);
        HashElem* cur = ht->data[i];
        for(;cur != NULL;cur = cur->next)
        {
            printf("[%d : %d] ",cur->key,cur->value);
        }
        printf("\n");
    }
    return;
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
    int ret = 0;
    ValType value;
    ret = HashFind(&ht,1002,&value);
    printf("ret expected 1 ,actual %d\n",ret);
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
    int ret = 0;
    ValType value;
    ret = HashFind(&ht,1002,&value);
    printf("ret expected 1 ,actual %d\n",ret);
    printf("value expected 12,actual %d\n",value);
    HashRemove(&ht,1002);
    ret = HashFind(&ht,1002,&value);
    printf("ret expected 0 ,actual %d\n",ret);
}
int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}
#endif
