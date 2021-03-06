#pragma once

typedef char LinkType;

typedef struct LinkNode
{
    LinkType data;
    struct LinkNode* next;
}LinkNode;

typedef struct LinkQueue
{
    LinkNode* head;
    LinkNode* tail;
}LinkQueue;

void LinkQueueInit(LinkQueue* q);
void LinkQueueDestroy(LinkQueue* q);
void LinkQueuePush(LinkQueue* q,LinkType value);
void LinkQueuePop(LinkQueue* q);
int LinkQueueFront(LinkQueue* q,LinkType* value);

