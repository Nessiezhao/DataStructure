#pragma once
#include<stdio.h>
#include<stddef.h>

#define HashMaxSize 1000

typedef int KeyType;
typedef int ValType;

typedef size_t (*HashFunc)(KeyType key);

//此结构体相当于是一个链表的节点
typedef struct HashElem
{
    KeyType key;
    ValType value;
    struct HashElem* next;
}HashElem;

typedef struct HashTable
{
    //如果我们的hash桶上的链表是一个不带头节点的链表（保存指针）
    //类型就用HashElem*
    //如果我们的hash桶上的链表是一个带头节点的链表（保存节点）
    //类型就用HashElem
    HashElem* data[HashMaxSize];
    size_t size;
    HashFunc func;
}HashTable;
