/*************************************************************************
	> File Name: LinkList.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2018年03月16日 星期五 19时48分43秒
 ************************************************************************/
#if 1
#include"LinkList.h"
#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
LinkNode* CreatNode(LinkNodeType value)
{
	LinkNode* new_node = (LinkNode*)malloc(sizeof(LinkNode));
	new_node->data = value;
	new_node->next=NULL;
	return new_node;
}

void DestroyNode(LinkNode* node)
{
	free(node);
}
void LinkNodeInit(LinkNode** node)
{
	*node= NULL;
}
void LinkListDestroy(LinkNode** phead)
{
	if(phead == NULL)
	{
		return;
	}
	if(*phead == NULL)
	{
		return;
	}
	LinkNode* cur = *phead;
	while(cur != NULL)
	{
		LinkNode* to_delete = cur;
		cur = cur->next;
		DestroyNode(to_delete);
	}
	*phead = NULL;
	
}



void LinkListPushBack(LinkNode** phead,LinkNodeType value)
{
	if(phead == NULL)
	{
		//非法输入
		return;
	}
	if(*phead == NULL)
	{
		//空链表
		*phead=CreatNode(value);
		return;
	}
	//链表非空
	LinkNode* cur=*phead;
	while(cur->next != NULL)
	{
		cur=cur->next;
	}
	LinkNode* new_node = CreatNode(value);
	cur->next = new_node;
	return;
}

void LinkListPopBack(LinkNode** phead)
{
	if(phead == NULL)
	{
		//非法输入
		return;
	}
	if(*phead == NULL)
	{
		//空链表，无法删除
		return;
	}
	if((*phead)->next == NULL)
	{
		//只有一个元素 
	    DestroyNode(*phead);
		*phead = NULL;
		return;
	}
	LinkNode* pos = *phead;
	LinkNode* cur = NULL;
	while(pos->next != NULL)
	{
		cur = pos;
		pos = pos->next;
	}
	DestroyNode(pos);
	pos = NULL;
	cur->next = NULL;

	return;
}

void LinkListPushFront(LinkNode** phead,LinkNodeType value)
{
	if(phead == NULL)
	{
		//非法输入
		return;
	}
	LinkNode* new_node = CreatNode(value);
	new_node->next = *phead;
	*phead = new_node;
	return;
}
void LinkListPopFront(LinkNode** phead)
{
	if(phead == NULL)
	{
		//非法输入
		return;
	}
	if(*phead ==NULL)
	{
		//空链表，无法删除
		return;
	}
	LinkNode* to_erase = *phead;
	*phead = (*phead)->next;
	DestroyNode(to_erase);
	to_erase == NULL;
	return;
}


LinkNode* LinkListFind(LinkNode* head,LinkNodeType to_find)
{
	if(head == NULL)
	{
		// 空链表
		return NULL;
	} 
	LinkNode* cur = head;
	while(cur != NULL)
	{
		if(cur->data == to_find)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}


void LinkListInsert(LinkNode* pos,LinkNodeType value)
{
	if(pos == NULL)
	{
		return;
	}
	LinkNode* new_node = CreatNode(value);
	new_node->next = pos->next;
	pos->next = new_node;
	return;
}


void LinkListInsertBefore(LinkNode** phead,LinkNode* pos,LinkNodeType value)
{
	if(phead == NULL || pos == NULL)
	{
		return;
	}
	if(*phead == pos)
	{
		LinkListPushFront(phead,value);
		return;
	}
	LinkNode* cur = *phead;
	for(;cur != NULL;cur=cur->next)
	{
		if(cur->next == pos)
		{
			break;
		}
	}
	if(cur == NULL)
	{
		return;
	}
	LinkListInsert(cur,value);
	return;

}
void LinkListInsertBefore2(LinkNode* pos,LinkNodeType value)
{
	if(pos == NULL)
	{
		return;
	}
	LinkListInsert(pos,pos->data);
	pos->data = value;
	return;
}
void LinkListErase(LinkNode** phead,LinkNode* pos)
{
	if(phead == NULL || pos == NULL)
	{
		return;
	}
	if(*phead == NULL)
	{
		return;
	}
	if(*phead == pos)
	{
		LinkListPopFront(phead);
	}
	LinkNode* cur = *phead;
	for(;cur != NULL; cur = cur->next)
	{
		if(cur ->next == pos)
		{
			cur->next = pos->next;
			DestroyNode(pos);
		}
	}
	return;
}
void LinkListErase2(LinkNode** phead,LinkNode* pos)
{
	if(phead == NULL || pos == NULL)
	{
		return;
	}
	if(*phead == NULL)
	{
		return;
	}
	if(pos->next == NULL)
	{
		//如果要删除的元素恰好是最后一个元素那就用为删
		LinkListPopBack(phead);
	}
	pos->data = pos->next->data;
	LinkNode* to_erase = pos->next;
	pos->next = to_erase->next;
	DestroyNode(to_erase);
	return;
}


void LinkListRemove(LinkNode** phead,LinkNodeType to_delete)
{
	if(phead == NULL)
	{
		return;
	}
	if(*phead == NULL)
	{
		return;
	}
	LinkNode* pos = *phead;
	while(pos->next != NULL)
	{
		if((pos == *phead) && (pos->data == to_delete))
		{
			LinkListPopFront(phead);
			return;
		}
		pos = pos->next;
		if(pos->data == to_delete)
		{
			LinkListErase(phead,pos);
			return;
		}
	}

}

void LinkListRemoveAll(LinkNode** phead,LinkNodeType value)
{
	if(phead == NULL)
	{
		return;
	}
	if(*phead == NULL)
	{
		return;
	}
	LinkNode* pos = *phead;
	while(1)
	{
		LinkNode* pos = LinkListFind(*phead,value);
		if(pos == NULL)
		{
			return;
		}
		LinkListErase(phead,pos);
	}
	return;

}

int LinkListEmpty(LinkNode* phead)
{
	if(phead == NULL)
	{
		return 1;
	}
	return 0;
}

size_t LinkListSize(LinkNode* phead)
{
	size_t count = 0;
	LinkNode* pos = phead;
	while(pos->next != NULL)
	{
		count++;
		pos = pos->next;
	}
	count++;
	return count;
}
void LinkListReversePrint(LinkNode* phead)
{
	if(phead == NULL)
	{
		return;
	}
	LinkNode* pos = phead;
	LinkListReversePrint(pos->next);
	printf("%c ",pos->data);
	return;
}
LinkNode* JosephCircle(LinkNode* phead,int M)
{
	if(phead == NULL)
	{
		return;
	}
	LinkNode* cur = phead;
	while(cur->next != cur)
	{
		int i = 1;
		for(;i<M;++i)
		{
			cur = cur->next;
		}
		printf("%c\n",cur->data);
		cur->data = cur->next->data;
		LinkNode* to_delete = cur->next;
		cur->next = to_delete->next;
		DestroyNode(to_delete);

	}
	return cur;

}
///////////////////////////////////////////////////////////////////
//常见的笔试题
////////////////////////////////////////////////////////////////
void LinkListReverse(LinkNode** phead)
{
	if(phead == NULL)
	{
		return;
	}
	if(*phead == NULL)
	{
		return;
	}
	if((*phead)->next==NULL)
	{
		//只有一个元素
		return;
	}
	LinkNode* pos = *phead;
	while(pos->next != NULL)
	{
		LinkNode* cur = pos->next;
		pos->next = cur->next;
		cur->next = *phead;
		*phead = cur;
	}
	return;
}
void LinkListReverse2(LinkNode** phead)
{
	if(phead == NULL)
	{
		return;
	}
	if(*phead == NULL)
	{
		return;
	}
	if((*phead)->next == NULL)
	{
		return;
	}
	LinkNode* cur = (*phead)->next;
	LinkNode* pre = *phead;
	pre->next = NULL;
	while(cur != NULL)
	{
		LinkNode* next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	*phead = pre;
	return;
}
void Swap(LinkNodeType* a,LinkNodeType* b)
{
	LinkNodeType tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}
void LinkListBubbleSort(LinkNode* phead)
{
	if(phead == NULL)
	{
		return;
	}
	LinkNode* tail = NULL;
	LinkNode* count = phead;
	for(;count != NULL;count=count->next)
	{
		LinkNode* cur = phead;
		for(;cur->next != tail;cur = cur->next)
		{
			if(cur->data > cur->next->data)
			{
				Swap(&cur->data,&cur->next->data);
			}
		}
		tail = cur;
	}
	return;
}

LinkNode* LinkListMerge(LinkNode* phead1,LinkNode* phead2)
{
	if(phead1 == NULL)
	{
		return phead2;
	}
	if(phead2 == NULL)
	{
		return phead1;
	}
	LinkNode* cur1 = phead1;
	LinkNode* cur2 = phead2;
	LinkNode* new_head = NULL;
	LinkNode* new_tail = NULL;
	while((cur1 != NULL )&& (cur2 != NULL))
	{
		if(cur1->data < cur2->data)
		{
			if(new_tail == NULL)
			{
				new_tail = new_head = cur1;
			}
			else
			{				
				new_tail->next = cur1;
				new_tail =new_tail->next;
			}
			cur1 = cur1->next;
		}
		else
		{
			if(new_tail == NULL)
			{
				new_tail = new_head = cur2;
			}
			else
			{				
				new_tail->next = cur2;
				new_tail =new_tail->next;
			}
			cur2 = cur2->next;

		}
	}
	if(cur1 != NULL)
	{
		new_tail->next = cur1;
	}
	if(cur2 != NULL)
	{
		new_tail->next = cur2;
	}
	return new_head;

}
LinkNode* LinkListFindMidNode(LinkNode* phead)
{
	if(phead == NULL)
	{
		return;
	}
	LinkNode* fast = phead;
	LinkNode* slow = phead;
	while((fast != NULL) && (fast->next != NULL))
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}
LinkNode* LinkListFindLastKNode(LinkNode* phead,int K)
{
	if(phead == NULL)
	{
		return NULL;
	}
	LinkNode* fast = phead;
	LinkNode* slow = phead;
	int i = 0;
	for(;i<K;++i)
	{
		fast = fast->next;
		if(fast == NULL)
		{
			break;
		}
	}
	if(i != K)
	{
		return NULL;
	}
	while(fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}
void LinkListEraseLastKNode(LinkNode** phead,int K)
{
	if(phead == NULL)
	{
		return;
	}
	if(*phead == NULL)
	{
		return;
	}
	int len = LinkListSize(*phead);
	if(K > len)
	{
		return;
	}
	if(K == len)
	{
		//要删除的元素为第一个所以用头删的方法
		LinkNode* to_erase = *phead;
		*phead = (*phead)->next;
		DestroyNode(to_erase);
	}
	LinkNode* pre = *phead;
	int i = 0;
	for(;i < len-1-K;++i)
	{
		pre = pre->next;
	}
	//循环结束pre指向K-1
	LinkNode* to_delete = pre->next;
	pre->next = to_delete->next;
	DestroyNode(to_delete);
	return;
}

LinkNode* LinkListHasCycle(LinkNode* phead)
{
	if(phead == NULL)
	{
		return NULL;
	}
	LinkNode* fast = phead;
	LinkNode* slow = phead;
	while((fast != NULL)&&(fast->next != NULL))
	{
		fast = fast->next->next;
		slow = slow->next;
		if(slow == fast)
		{
			return slow;
		}
	}
	return NULL;
}

size_t LinkListCycleLen(LinkNode* phead)
{
	if(phead == NULL)
	{
		return 0;
	}
	LinkNode* meet_node = LinkListHasCycle(phead);
	if(meet_node == NULL)
	{
		return 0;
	}
	LinkNode* cur = meet_node->next;
	size_t len = 1;
	while(cur != meet_node)
	{
		cur = cur->next;
		++len;
	}
	return len;
}
LinkNode* LinkListCycleEntry(LinkNode* phead)
{
	if(phead == NULL)
	{
		return NULL;
	}
	LinkNode* meet_node = LinkListHasCycle(phead);
	if(meet_node == NULL)
	{
		return;
	}
	LinkNode* cur1 = phead;
	LinkNode* cur2 = meet_node;
	while(cur1 != cur2)
	{
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;
}
int LinkListHasCross(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return 0;
	}
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	while(cur1 != NULL)	
	{
		cur1 = cur1->next;
	}
	while(cur2 != NULL)	
	{
		cur2 = cur2->next;
	}
	return cur1 == cur2 ? 1 : 0;
}

LinkNode* LinkListCrossPos(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	size_t len1 = LinkListSize(head1);
	size_t len2 = LinkListSize(head2);
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	if(len1 > len2)
	{
		size_t offset = len1 - len2;
		int i = 0;
		for(i = 0;i < offset;++i)
		{
			cur1 = cur1->next;
		}
		while(cur1 != NULL && cur2 != NULL)
		{
			if(cur1 == cur2)
			{
				return cur1;
			}
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
	}
	if(len1 < len2)
	{
		size_t offset = len2 - len1;
		int i = 0;
		for(i = 0;i < offset;++i)
		{
			cur2 = cur2->next;
		}
		while(cur1 != NULL && cur2 != NULL)
		{
			if(cur1 == cur2)
			{
				return cur1;
			}
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
	}
	return NULL;
}
int LinkListHasCrossWithCycle(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL && head2 == NULL)
	{
		return 0;
	}
	//分别求两个链表的环的入口
	LinkNode* entry1 = LinkListCycleEntry(head1);
	LinkNode* entry2 = LinkListCycleEntry(head2);
	//两个链表都不带环，直接使用前面的方式判定相交
	if(entry1 == NULL && entry2 == NULL)
	{
		return LinkListHasCross(head1,head2);
	}
	//如果一个带环一个不带环，那么直接返回不相交
	if((entry1 == NULL && entry2 != NULL)||
		(entry2 == NULL && entry1 != NULL))
	{
		return 0;
	}
	//如果两个链表都带环
	//a）如果这两个入口点重合，说明相交，并且是环外相交
	if(entry1 == entry2)
	{
		return 1;
	}
	//b）如果从一个入口点出发，绕环一周，能到达第二个入口点
	//   说明也是相交，并且是环上相交
	LinkNode* cur = entry1->next;
	while(cur != entry1)
	{
		if(cur == entry2)
		{
			return 1;
		}
		cur = cur->next;
	}
	//c）如果不是上面两种情况，就说明不相交
	return 0;	
}
LinkNode* LinkListCrossWithCyclePos(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	//交点在环上则为两个环的入口点
	LinkNode* entry1 = LinkListCycleEntry(head1);
	LinkNode* entry2 = LinkListCycleEntry(head2);
	if(entry1 != entry2)
	{
		LinkNode* cur = entry1;
		for(;cur!=entry2;cur = cur->next);
		return entry2;
		cur = entry2;
		/*for(;cur!=entry1;cur = cur->next);
		return entry1;*/
	}
	//交点在环外
	else if(entry1 == entry2)
	{
		size_t len1 = LinkListSize(head1) -LinkListSize(entry1);
		size_t len2 = LinkListSize(head2) -LinkListSize(entry1);
		LinkNode* cur1 = head1;
		LinkNode* cur2 = head2;
		if(len1 > len2)
		{
			size_t offset = len1 - len2;
			int i = 0;
			for(i = 0;i < offset;++i)
			{
				cur1 = cur1->next;
			}
			while(cur1 != NULL && cur2 != NULL)
			{
				if(cur1 == cur2)
				{
					return cur1;
				}
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
		}
		if(len1 < len2)
		{
			size_t offset = len2 - len1;
			int i = 0;
			for(i = 0;i < offset;++i)
			{
				cur2 = cur2->next;
			}
			while(cur1 != NULL && cur2 != NULL)
			{
				if(cur1 == cur2)
				{
					return cur1;
				}
				cur1 = cur1->next;

				cur2 = cur2->next;
			}
		}
	}
	else
	{
		return NULL;
	}
}
LinkNode* LinkListUnionSet(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	LinkNode* new_head = NULL;
	LinkNode* new_tail = NULL;
	while((cur1 != NULL) &&( cur2 != NULL))
	{
		if(cur1->data < cur2->data)
		{
			cur1 = cur1->next;
		}
		else if(cur2->data < cur1->data)
		{
			cur2 = cur2->next;
		}
		//两个相等
		else
		{
			if(new_head == NULL)
			{
				new_head = new_tail = CreatNode(cur1->data);
			}
			else
			{
				new_tail->next = CreatNode(cur1->data);
				new_tail = new_tail->next;
			}
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
	}
	return new_head;
}
typedef struct ComplexNode
{
	LinkNodeType data;
	struct ComplexNode* next;
	struct ComplexNode* random;
}ComplexNode;

ComplexNode* CreateComplexNode(LinkNodeType value)
{
	ComplexNode* new_node = (ComplexNode*)malloc(sizeof(ComplexNode));
	new_node->data = value;
	new_node->next = NULL;
	new_node->random = NULL;
	return new_node;
}
size_t Diff(ComplexNode* src,ComplexNode* dest)
{
	size_t offset = 0;
	while(src != NULL)
	{
		if(src == dest)
		{
			break;
		}
		++offset;
		src = src->next;
	}
	if(src == NULL)
	{
		return (size_t)-1;
	}
	return offset;
}
ComplexNode* Step(ComplexNode* head,size_t offset)
{
	ComplexNode* cur = head;
	size_t i = 0;
	while(1)
	{
		if(cur == NULL)
		{
			return NULL;
		}
		if(i >= offset)
		{
			return cur;
		}
		++i;
		cur = cur->next;
	}
	return NULL;
}

ComplexNode* CopyComplexList(ComplexNode* head)
{
	//先按照简单链表进行复制
	ComplexNode* new_head = NULL;
	ComplexNode* new_tail = NULL;
	ComplexNode* cur = head;
	for(;cur != NULL;cur = cur->next)
	{
		ComplexNode* new_node = CreateComplexNode(cur->data);
		if(new_head == NULL)
		{
			new_head = new_tail = new_node;
		}
		else
		{
			new_tail->next = new_node;
			new_tail = new_tail->next;
		}
	}

	//遍历旧链表，找到每个链表节点random指针相对于链表头部的偏移量
	//遍历新链表，根据偏移量，设置新链表的random
	ComplexNode* new_cur = new_head;
	for(cur = head;cur != NULL;cur = cur->next,new_cur = new_cur->next)
	{
		if(cur->random == NULL)
		{
			new_cur->random = NULL;
			continue;
		}
		//通过Diff函数，计算出链表的两个节点的偏移量
		size_t offset = Diff(head,cur->random)	;
		//通过Step函数，相当于求出从new_head出发，走了offset步，到达的位置是谁
		new_cur->random = Step(new_head,offset);
	}
	return new_head;
}

ComplexNode* CopyComplexList2(ComplexNode* head)
{
	//遍历链表，给每个节点后插入新的节点
	ComplexNode* cur = head;
	for(;cur != NULL;cur = cur->next->next)
	{
		ComplexNode* new_node = CreateComplexNode(cur->data);
		new_node->next = cur->next;
		cur->next = new_node;
	}
	//维护新结点的random指针
	for(cur = head;cur != NULL;cur = cur->next->next)
	{
		ComplexNode* new_cur = cur->next;
		if(cur->random == NULL)
		{
			new_cur->random == NULL;
			continue;
		}
		new_cur->random = cur->random->next;
	}
	//将新结点拆除
	ComplexNode* new_head = NULL;
	ComplexNode* new_tail = NULL;
	for(cur = head;cur != NULL;cur = cur->next)
	{
		ComplexNode* new_cur = cur->next;
		cur->next = new_cur->next;
		if(new_head == NULL)
		{
			new_head = new_tail = new_cur;
		}
		else
		{
			new_tail->next = new_cur;
			new_tail = new_tail->next;
		}
	}
	return new_head;
}
//前方高能！！！非大佬请勿模仿，为C++代码
/*#include<unordered_map>
ComplexNode* CopyComplexList3(ComplexNode* head)
{
	std::unordered_map<ComplexNode*,ComplexNode*>table;
	for(ComplexNode* cur = head;cur != NULL;cur = cur->next)
	{
		table[cur] = CreateComplexNode(cur->data);
	}
	for( cur = head;cur != NULL;cur = cur->next)
	{
		table[cur]->random = table[cur->random];
	}
	return table[head];
}*/
///////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#define TEST_HEADER printf("\n=============================%s============================\n",__FUNCTION__);
void LinkListPrintChar(LinkNode* head,const char* msg)
{
	printf("[%s]\n",msg);
	LinkNode* cur = head;
	for(;cur != NULL;cur = cur->next)
	{
		printf("[%c|%p]",cur->data,cur);
	}
	printf("\n");
}
void TestInit()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
//	LinkNodeInit(NULL);
}

void TestPushBack()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPrintChar(head,"尾插四个元素");

}
void TestPopBack()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPopBack(&head);
	LinkListPrintChar(head,"对空链表进行删除");

	LinkListPushBack(&head,'a');
	LinkListPopBack(&head);
	LinkListPrintChar(head,"对只有一个元素的链表进行删除");

	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPopBack(&head);
	LinkListPopBack(&head);
	LinkListPrintChar(head,"尾删两个元素");

}
void TestPushFront()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushFront(&head,'a');
	LinkListPushFront(&head,'b');
	LinkListPushFront(&head,'c');
	LinkListPushFront(&head,'d');
	LinkListPrintChar(head,"头插四个元素");

}
void TestPopFront()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPopFront(&head);
	LinkListPopFront(&head);
	LinkListPrintChar(head," 头删两个元素");

}

void TestFind()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');

	LinkNode* pos = LinkListFind(head,'a');
	printf("expect : %p  ,actual : %p\n",head,pos);
	LinkNode* pos2 = LinkListFind(head,'x');
	printf("expect :NULL  ,actual : %p\n",pos2);

}

void TestInsert()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	
	LinkNode* pos = head->next;
	LinkListInsert(pos,'x');
	LinkListPrintChar(head," 在 b 后插入 x");
}

void TestInsertBefore()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	
	LinkNode* pos =head;
	LinkListInsertBefore(&head,pos,'x');
	LinkListPrintChar(head," 在 a 前插入 x");
	LinkNode* pos2 =head->next->next;
	LinkListInsertBefore(&head,pos2,'x');
	LinkListPrintChar(head," 在 b 前插入 x");
}

void TestInsertBefore2()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	
	LinkNode* pos =head;
	LinkListInsertBefore(&head,pos,'x');
	LinkListPrintChar(head," 在 a 前插入 x");
	LinkNode* pos2 =head->next->next;
	LinkListInsertBefore(&head,pos2,'x');
	LinkListPrintChar(head," 在 b 前插入 x");
}

void TestErase()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListErase(&head,(LinkNode*)0x11);
	LinkListPrintChar(head,"对空链表进行删除");

	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');

	LinkNode* pos = head->next;
	LinkListErase(&head,pos);
	LinkListPrintChar(head,"删除元素 b ");

	LinkNode* pos2 = (LinkNode*)0x10;
	LinkListErase(&head,pos2);
	LinkListPrintChar(head,"尝试对一个不存在的数进行删除");
	
}
void TestErase2()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListErase2(&head,(LinkNode*)0x11);
	LinkListPrintChar(head,"对空链表进行删除");

	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');

	LinkNode* pos3 = head->next;
	LinkListErase2(&head,pos3);
	LinkListPrintChar(head,"删除元素 b ");

//	LinkNode* pos4 = (LinkNode*)0x10;
//	LinkListErase2(&head,pos4);
//	LinkListPrintChar(head,"尝试对一个不存在的数进行删除");
	
}

void TestRemove()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'b');

	LinkListRemove(&head,'b');
	LinkListPrintChar(head,"删除链表中第一个值为 b 的元素");

}
void TestRemoveAll()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'b');

	LinkListRemoveAll(&head,'b');
	LinkListPrintChar(head,"删除链表中值为 b 的元素");

}

void TestEmpty()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	int a = LinkListEmpty(head);
	printf("%d\n",a);
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	int b = LinkListEmpty(head);
	printf("%d\n",b);

}
void TestSize()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'b');

	LinkListPrintChar(head,"链表中的元素");
	size_t a = LinkListSize(head);
	printf("%d个\n",a);
}
void TestReversePrint()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');

	LinkListReversePrint(head);
}

void TestJosephCircle()
{
	TEST_HEADER;
	LinkNode* a = CreatNode('a');
	LinkNode* b = CreatNode('b');
	LinkNode* c = CreatNode('c');
	LinkNode* d = CreatNode('d');
	LinkNode* e = CreatNode('e');
	LinkNode* f = CreatNode('f');
	LinkNode* g = CreatNode('g');
	LinkNode* h = CreatNode('h');
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = f;
	f->next = g;
	g->next = h;
	h->next = a;
	LinkNode* survive = JosephCircle(a,5);
	printf("survive is %c\n",survive->data);

}
void TestDestroy()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListDestroy(&head);
	LinkListPrintChar(head,"删除链表中的元素");


}
void TestReverse()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListReverse(&head);
	LinkListPrintChar(head,"逆置链表");

}
void TestReverse2()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListReverse2(&head);
	LinkListPrintChar(head,"逆置链表");

}
void TestBubbleSort()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'b');
	LinkListBubbleSort(head);
	LinkListPrintChar(head,"冒泡排序");

}
void TestMerge()
{
	TEST_HEADER;
	LinkNode* head1;
	LinkNode* head2;
	LinkNode* head3;
	LinkNodeInit(&head1);
	LinkNodeInit(&head2);
	LinkNodeInit(&head3);
	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'e');
	LinkListPushBack(&head1,'g');
	LinkListPushBack(&head2,'b');
	LinkListPushBack(&head2,'d');
	LinkListPushBack(&head2,'f');
	LinkListPushBack(&head2,'h');
	head3 = LinkListMerge(head1,head2);
	LinkListPrintChar(head3,"将已经有序的链表合并成一个有序的链表");

}
void TestFindMidNode()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'e');
	LinkNode* p = LinkListFindMidNode(head);
	LinkListPrintChar(head,"查找链表的中间元素");
	printf("mid expect c,actual %c\n",*p);

}
void TestFindLastKNode()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'e');
	LinkNode* p = LinkListFindLastKNode(head,2);
	LinkListPrintChar(head,"查找倒数第二个元素");
	printf("mid expect d,actual %c\n",*p);
	
}
void TestEraseLastKNode()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'e');
	LinkListEraseLastKNode(&head,2);
	LinkListPrintChar(head,"删除倒数第二个元素");
}

void TestHasCycle()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'e');
	LinkNode* pow_e = LinkListFind(head,'e');
	pow_e->next = head->next->next;
	LinkNode* p = LinkListHasCycle(head);
	printf("%c\n",*p);
	
}

void TestCycleLen()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'e');
	LinkNode* pow_e = LinkListFind(head,'e');
	pow_e->next = head->next->next;
	size_t p = LinkListCycleLen(head);
	printf("%d\n",p);

}
void TestCycleEntry()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'b');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'d');
	LinkListPushBack(&head,'e');
	LinkNode* pow_e = LinkListFind(head,'e');
	pow_e->next = head->next->next;
	LinkNode* p = LinkListCycleEntry(head);
	printf("%c\n",*p);

}
void TestHasCross()
{
	TEST_HEADER;
	LinkNode* head1;
	LinkNodeInit(&head1);
	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');
	LinkListPushBack(&head1,'e');

	LinkNode* head2;
	LinkNodeInit(&head2);
	LinkListPushBack(&head2,'a');
	LinkListPushBack(&head2,'b');
	LinkListPushBack(&head2,'c');

	LinkNode* pos_c = LinkListFind(head2,'c');
	pos_c->next = head1->next;
	int ret = LinkListHasCross(head1,head2);
	printf("ret : expected 1 ,actual %d\n",ret);
}
void TestCrossPos()
{
	TEST_HEADER;
	LinkNode* head1;
	LinkNodeInit(&head1);
	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');
	LinkListPushBack(&head1,'e');

	LinkNode* head2;
	LinkNodeInit(&head2);
	LinkListPushBack(&head2,'a');
	LinkListPushBack(&head2,'b');
	LinkListPushBack(&head2,'c');

	LinkNode* pos_c = LinkListFind(head2,'c');
	pos_c->next = head1->next;
	LinkNode* pos = LinkListCrossPos(head1,head2);
	printf("pos : expected b ,actual %c\n",pos->data);

}
void TestHasCrossWithCycle()
{
	//两个链表都不带环
	TEST_HEADER;
	LinkNode* head1;
	LinkNodeInit(&head1);
	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');
	LinkListPushBack(&head1,'e');

	LinkNode* head2;
	LinkNodeInit(&head2);
	LinkListPushBack(&head2,'a');
	LinkListPushBack(&head2,'b');
	LinkListPushBack(&head2,'c');

	LinkNode* pos_c = LinkListFind(head2,'c');
	pos_c->next = head1->next;
	int ret1 = LinkListHasCrossWithCycle(head1,head2);
	printf("ret1 : expected 1 ,actual %d\n",ret1);
	
	//一个带环一个不带环
	LinkNode* head3;
	LinkNodeInit(&head3);
	LinkListPushBack(&head3,'a');
	LinkListPushBack(&head3,'b');
	LinkListPushBack(&head3,'c');
	LinkListPushBack(&head3,'d');
	LinkListPushBack(&head3,'e');
	LinkNode* pow_e = LinkListFind(head3,'e');
	pow_e->next = head3->next->next;

	LinkNode* head4;
	LinkNodeInit(&head4);
	LinkListPushBack(&head4,'a');
	LinkListPushBack(&head4,'b');
	LinkListPushBack(&head4,'c');
	LinkListPushBack(&head4,'d');
	LinkListPushBack(&head4,'e');
	int ret2 = LinkListHasCrossWithCycle(head3,head4);
	printf("ret2 : expected 0 ,actual %d\n",ret2);
	//两个入口点重合，环外相交
	LinkNode* head5;
	LinkNodeInit(&head5);
	LinkListPushBack(&head5,'a');
	LinkListPushBack(&head5,'b');
	LinkListPushBack(&head5,'c');
	LinkListPushBack(&head5,'d');
	LinkListPushBack(&head5,'e');
	LinkListPushBack(&head5,'f');
	LinkListPushBack(&head5,'g');
	LinkNode* pos_g = LinkListFind(head5,'g');
	pos_g->next = head5->next->next->next;

	LinkNode* head6;
	LinkNodeInit(&head6);
	LinkListPushBack(&head6,'a');
	LinkListPushBack(&head6,'b');
	LinkNode* pos_b = LinkListFind(head6,'b');
	pos_b->next = head5->next->next;
	int ret3 = LinkListHasCrossWithCycle(head5,head6);
	printf("ret3 : expected 1 ,actual %d\n",ret3);

	//环上相交
	LinkNode* head7;
	LinkNodeInit(&head7);
	LinkListPushBack(&head7,'a');
	LinkListPushBack(&head7,'b');
	LinkListPushBack(&head7,'c');
	LinkListPushBack(&head7,'d');
	LinkListPushBack(&head7,'e');
	LinkListPushBack(&head7,'f');
	LinkListPushBack(&head7,'g');
	LinkListPushBack(&head7,'h');
	LinkNode* pos_h = LinkListFind(head7,'h');
	pos_h->next = head7->next->next->next;

	LinkNode* head8;
	LinkNodeInit(&head8);
	LinkListPushBack(&head8,'a');
	LinkListPushBack(&head8,'b');
	LinkListPushBack(&head8,'c');
	LinkListPushBack(&head8,'d');
	LinkNode* pos_d = LinkListFind(head8,'c');
	pos_d->next = head7->next->next->next;
	int ret4 = LinkListHasCrossWithCycle(head7,head8);
	printf("ret4 : expected 1 ,actual %d\n",ret4);

}
void TestCrossWithCyclePos()
{
	TEST_HEADER;
	//环外相交
	LinkNode* head1;
	LinkNodeInit(&head1);
	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');
	LinkListPushBack(&head1,'e');
	LinkListPushBack(&head1,'f');
	LinkListPushBack(&head1,'g');
	LinkNode* pos_g = LinkListFind(head1,'g');
	pos_g->next = head1->next->next->next;
	int i = 0;
	for(;i<10;i++)
	{
		LinkNode* a = head1;
		printf("[%c] ",a->data);
		a = a->next;
	}

	LinkNode* head2;
	LinkNodeInit(&head2);
	LinkListPushBack(&head2,'a');
	LinkListPushBack(&head2,'b');
	LinkListPushBack(&head2,'c');
	LinkNode* pos_c = LinkListFind(head2,'c');
	pos_c->next = head1->next;
	int j = 0;
	for(;j<10;j++)
	{
		LinkNode* a = head2;
		printf("[%c] ",a->data);
		a = a->next;
	}
	LinkNode* pos1 = LinkListCrossWithCyclePos(head1,head2);
	printf("pos : expected b,actual %c\n",pos1->data);

	//环上相交
	LinkNode* head3;
	LinkNodeInit(&head3);
	LinkListPushBack(&head3,'a');
	LinkListPushBack(&head3,'b');
	LinkListPushBack(&head3,'c');
	LinkListPushBack(&head3,'d');
	LinkListPushBack(&head3,'e');
	LinkListPushBack(&head3,'f');
	LinkListPushBack(&head3,'g');
	LinkListPushBack(&head3,'h');
	LinkNode* pos_h = LinkListFind(head3,'h');
	pos_h->next = head3->next->next->next;

	LinkNode* head4;
	LinkNodeInit(&head4);
	LinkListPushBack(&head4,'a');
	LinkListPushBack(&head4,'b');
	LinkListPushBack(&head4,'c');
	LinkListPushBack(&head4,'d');
	LinkNode* pos_d = LinkListFind(head4,'d');
	pos_d->next = head3->next->next->next->next;
	LinkNode* pos2 = LinkListCrossWithCyclePos(head3,head4);
	printf("pos : expected  e,actual %c\n",pos2->data);
	
}
void TestUnionSet()
{
	TEST_HEADER;
	LinkNode* head1;
	LinkNodeInit(&head1);
	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');
	LinkListPushBack(&head1,'e');

	LinkNode* head2;
	LinkNodeInit(&head2);
	LinkListPushBack(&head2,'b');
	LinkListPushBack(&head2,'c');
	LinkNode* head = LinkListUnionSet(head1,head2);
	LinkListPrintChar(head,"两个已排序单链表中的相同元素");

}
void PrintComplexList(ComplexNode* head,const char* msg)
{
	printf("[%s]\n",msg);
	ComplexNode* cur = head;
	for(;cur != NULL;cur = cur->next)
	{
		printf("[%c] ",cur->data);
	}
	printf("\n");
	for(cur = head ;cur != NULL;cur =cur->next)
	{
		if(cur->random == NULL)
		{
			printf("[NULL] ");
			continue;
		}
		printf("[%c] ",cur->random->data);
	}
	printf("\n");

}
void TestCopyComplexList()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	ComplexNode* a = CreateComplexNode('a');
	ComplexNode* b = CreateComplexNode('b');
	ComplexNode* c = CreateComplexNode('c');
	ComplexNode* d = CreateComplexNode('d');
	ComplexNode* e = CreateComplexNode('e');
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next =NULL;
	a->random = c;
	b->random = a;
	c->random = NULL;
	d->random = d;
	e->random = c;

	ComplexNode* new_head = CopyComplexList(a);
	PrintComplexList(new_head,"拷贝复杂链表");
}
void TestCopyComplexList2()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	ComplexNode* a = CreateComplexNode('a');
	ComplexNode* b = CreateComplexNode('b');
	ComplexNode* c = CreateComplexNode('c');
	ComplexNode* d = CreateComplexNode('d');
	ComplexNode* e = CreateComplexNode('e');
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next =NULL;
	a->random = c;
	b->random = a;
	c->random = NULL;
	d->random = d;
	e->random = c;

	ComplexNode* new_head = CopyComplexList2(a);
	PrintComplexList(new_head,"拷贝复杂链表");
}
/*void TestCopyComplexList3()
{
	TEST_HEADER;
	LinkNode* head;
	LinkNodeInit(&head);
	ComplexNode* a = CreateComplexNode('a');
	ComplexNode* b = CreateComplexNode('b');
	ComplexNode* c = CreateComplexNode('c');
	ComplexNode* d = CreateComplexNode('d');
	ComplexNode* e = CreateComplexNode('e');
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next =NULL;
	a->random = c;
	b->random = a;
	c->random = NULL;
	d->random = d;
	e->random = c;

	ComplexNode* new_head = CopyComplexList3(a);
	PrintComplexList(new_head,"拷贝复杂链表");
}*/
int main()
{
	TestInit();
	TestPopBack();
	TestPushBack();
	TestPushFront();
	TestPopFront();
	TestFind();
	TestInsert();
	TestInsertBefore();
	TestInsertBefore2();
	TestErase();
	TestErase2();
	TestRemove();
	TestRemoveAll();
	TestEmpty();
	TestSize();
	TestReversePrint();
	TestJosephCircle();
	TestDestroy();
	TestReverse();
	TestReverse2();
	TestBubbleSort();
	TestMerge();
	TestFindMidNode();
	TestFindLastKNode();
	TestEraseLastKNode();
	TestHasCycle();
	TestCycleLen();
	TestCycleEntry();
	TestHasCross();
	TestCrossPos();
	TestHasCrossWithCycle();
	TestCrossWithCyclePos();
	TestUnionSet();
	TestCopyComplexList();
	TestCopyComplexList2();
	//TestCopyComplexList3();
	return 0;
}

#endif
