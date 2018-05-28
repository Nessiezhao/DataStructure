#pragma once
#include"bitmap.h"
//此处定义了布隆过滤器的哈希函数，把字符串转成下标
typedef uint64_t (*BloomHash)(const char*);
#define BloomHashCount 2

typedef struct BloomFilter
{
    Bitmap bm;
    BloomHash bloom_hash[BloomHashCount];
}BloomFilter;

void BloomFilterInit(BloomFilter* bf);

void BloomFilterDestroy(BloomFilter* bf);

void BloomFilterInsert(BloomFilter* bf,const char* str);

void BloomFilterIsExist(BloomFilter* bf,const char* str);
