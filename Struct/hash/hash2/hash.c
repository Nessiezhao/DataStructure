#include"hash.h"
#include <stdio.h>
#include<stddef.h>

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
int main()
{
    TestInit();
    return 0;
}
#endif
