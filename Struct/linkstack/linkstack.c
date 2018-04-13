#include"linkstack.h"
#include <stdio.h>
#include<stdlib.h>
void LinkStackInit(LinkStack* s)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
    s->head = NULL;
    s->tail = NULL;
    return;
}
void LinkStackDestroy(LinkStack* s)
{
    if(s == NULL)
    {
        //非法输入
        return;
    }
    
}
LinkNode* CreateLinkStackNode(LinkStackType value)
{
    LinkNode* tmp = (LinkNode*)malloc(sizeof(LinkNode));
    if(!tmp)
    {
        //创建失败
        return NULL;
    }
    tmp->data = value;
    tmp->next = NULL;
    return tmp;
}
void LinkStackPush(LinkStack* s,LinkStackType value)
{
    if(s == NULL)
    {
        return;
    }
    LinkNode* cur = CreateLinkStackNode(value);
    cur->next = s->head;
    s->head = cur;
    return;
}
void DestroyLinkStackNode(LinkNode* to_delete)
{
    if(to_delete == NULL)
    {
        return;
    }
    free(to_delete);
    to_delete = NULL;
    return;
}

void LinktackPop(LinkStack* s)
{
    if(s == NULL)
    {
        return;
    }
    LinkNode* to_delete = s->head;
    s->head = s->head->next;
    DestroyLinkStackNode(to_delete);
    return;
}
int LinkStackTop(LinkStack* s,LinkStackType* value)
{
    if(s == NULL || value == NULL)
    {
        return 0;
    }
    if(s->head == NULL)
    {
        return 0;
    }
    *value = s->head->data;
    return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n=========================%s===================================\n",__FUNCTION__);
void TestStack()
{
    TEST_HEADER;
    LinkStack stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack,'a');
    LinkStackPush(&stack,'b');
    LinkStackPush(&stack,'c');
    LinkStackPush(&stack,'d');

    LinkStackType value;
    int ret = LinkStackTop(&stack,&value);
    printf("ret expected : 1,actual %d\n",ret);
    printf("value expected : d,actual %c\n",value);
    LinktackPop(&stack);
    ret = LinkStackTop(&stack,&value);
    printf("ret expected : 1,actual %d\n",ret);
    printf("value expected : c,actual %c\n",value);
    LinktackPop(&stack);
    ret = LinkStackTop(&stack,&value);
    printf("ret expected : 1,actual %d\n",ret);
    printf("value expected : b,actual %c\n",value);
    LinktackPop(&stack);
    ret = LinkStackTop(&stack,&value);
    printf("ret expected : 1,actual %d\n",ret);
    printf("value expected : a,actual %c\n",value);
    LinktackPop(&stack);
    ret = LinkStackTop(&stack,&value);
    printf("ret expected : 0,actual %d\n",ret);
}

int main()
{
    TestStack();
    return 0;
}
#endif

