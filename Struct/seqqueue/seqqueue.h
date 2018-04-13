#pragma once
#include<stddef.h>

typedef char SeqQueueType;

#define SeqQueueMaxSize 1000

typedef struct SeqQueue
{
    SeqQueueType data[SeqQueueMaxSize];
    size_t head;
    size_t tail;
    size_t size;
}SeqQueue;

void SeqQueueInit(SeqQueue* q);
void SeqQueueDestroy(SeqQueue* q);
void SeqQueuePush(SeqQueue* q,SeqQueueType value);
void SeqQueuePop(SeqQueue* q);
int SeqQueueFront(SeqQueue* q,SeqQueueType* value);
