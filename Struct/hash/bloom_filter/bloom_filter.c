#include"bloom_filter.h"
#include <stdio.h>
#include"hash_func.c"
void BloomFilterInit(BloomFilter* bf)
{
    if(bf == NULL)
    {
        return;
    }
    BitmapInit(&bf->bm,10000);
    bf->bloom_hash[0] = SDBMHash;
    bf->bloom_hash[1] = BKDRHash;
    return;
}

void BloomFilterDestroy(BloomFilter* bf)
{
    if(bf == NULL)
    {
        return;
    }
    bf->bloom_hash[0] = NULL;
    bf->bloom_hash[1] = NULL;
    BitmapDestroy(&bf->bm);
    return;
}

void BloomFilterInsert(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        //非法输入
        return;
    }
    size_t i = 0;
    for(;i < BloomHashCount;++i)
    {
        uint64_t hash = bf->bloom_hash[i](str) % BitmapMaxSize;
        BitmapSet(&bf->bm,hash);
    }
    return;
}

int BloomFilterIsExist(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        //非法输入
        return 0;
    }
    size_t i = 0;
    for(;i < BloomHashCount;++i)
    {
        uint64_t hash = bf->bloom_hash[i](str) % BitmapMaxSize;
        int ret = BitmapTest(&bf->bm,hash);
        if(ret == 0)
        {
            return 0;
        }
    }
    return 1;
}
///////////////////////////////////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n==========================%s============================\n",__FUNCTION__);
void TestBloom()
{
    TEST_HEADER;
    BloomFilter bf;
    BloomFilterInit(&bf);
    BloomFilterInsert(&bf,"nihao");
    BloomFilterInsert(&bf,"haha");
    int ret = BloomFilterIsExist(&bf,"nihao");
    printf("ret expected 1,actual %d\n",ret);
    ret = BloomFilterIsExist(&bf,"hehe");
    printf("ret expected 0,actual %d\n",ret);
}
int main()
{
    TestBloom();
    return 0;
}
#endif

