#pragma once

typedef char LinkStackType;

typedef struct LinkNode
{
    LinkStackType data;
    struct LinkNode* next;
}LinkNode;

typedef struct LinkStack
{
    LinkNode* head;
    LinkNode* tail;
}LinkStack;

void LinkStackInit(LinkStack* s);
void LinkStackDestroy(LinkStack* s);
void LinkStackPush(LinkStack* s,LinkStackType value);
void LinkStackPop(LinkStack* s);
int LinkStackTop(LinkStack* s ,LinkStackType* value);

