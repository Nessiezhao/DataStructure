#pragma once
#include<stdio.h>
#include<stddef.h>
//我们此处存放的hash表期望存储的数据是键值对这样的结构
#define HashMaxSize 1000

typedef enum
{
    Empty,//空状态
    Deleted,//被删除的状态
    Valid,//有效状态
}Stat;

typedef int KeyType;
typedef int ValType;

typedef size_t (*HashFunc)(KeyType key);

//这个结构体表示hash表中的一个元素
//这个元素中同时包含了键值对
typedef struct HashElem
{
    KeyType key;
    ValType value;
    Stat stat;
}HashElem;

//[0,size)这个区间就不能表示hash表中有效元素
typedef struct HashTable
{
    HashElem data[HashMaxSize];
    size_t size;
    HashFunc func;//这是一个函数指针
}HashTable;
