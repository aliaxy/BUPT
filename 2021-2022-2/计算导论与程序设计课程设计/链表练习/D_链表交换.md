## 链表交换

已知一个正整数序列，序列元素个数未知，但至少有两个元素，你的任务是建立一个单链表用于存储这个正整数序列。然后实现交换此链表中任意指定的两段，第一段为[s1,t1]，第二段[s2,t2]。s1、t1、s2、t2代表链表的第几个节点，且满足s1<=t1，s2<=t2，t1<s2，s2一定小于等于链表节点的总个数。正整数的输入用-1作为结束标志，注意-1不算这个正整数序列中的元素（不要统计-1）。最后将链表的全部节点释放。

#### Input

输入一个正整数序列，以输入“-1”结束，序列中元素个数未知，但输入“-1”前至少输入两个正整数。然后是四个整数，即为s1、t1、s2、t2。

#### Output

经过处理后的新链表，每个元素后有一个空格，注意最后一个元素后只有换行符。
数据最多的测试用例节点数在100这个数量级，所有整数可以用int型存储。
**请注意输入输出格式。**

#### Sample Input

```
1 2 3 4 5 6 7 8 9 10 -1
1 1 4 7
```

#### Sample Ouput

```
The new list is:4 5 6 7 2 3 1 8 9 10
```

#### Solution

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

struct test
{
	int val;
	struct test *nextPtr;
};
typedef struct test Node;

Node *CreateList();
void SortList(Node *headPtr);
void PrintList(Node *headPtr);
void FreeList(Node *headPtr);
bool IsSubSequence(Node *headPtrA, Node *headPtrB);
Node *FindPosInList(Node *headPtr, int n);
void ExchangeRange(Node **headPtr, int l1, int r1, int l2, int r2);

int main(void)
{
	Node *headPtr = CreateList();

	ExchangeRange(&headPtr, read(), read(), read(), read());
	PrintList(headPtr);
	FreeList(headPtr);

	return 0;
}

Node *CreateList()
{
	Node *headPtr = NULL, *curPtr, *lastPtr;
	int num = read();
	while (~num)
	{
		curPtr = (Node *) malloc(sizeof(Node));
		curPtr->val = num, curPtr->nextPtr = NULL;
		if (!headPtr)
			headPtr = lastPtr = curPtr;
		else
		{
			lastPtr->nextPtr = curPtr;
			lastPtr = curPtr;
		}
		num = read();
	}
	lastPtr->nextPtr = NULL;
	return headPtr;
}

void PrintList(Node *headPtr)
{
	printf("The new list is:%d", headPtr->val);
	headPtr = headPtr->nextPtr;
	while (headPtr)
	{
		printf(" %d", headPtr->val);
		headPtr = headPtr->nextPtr;
	}
	putchar('\n');
}

void FreeList(Node *headPtr)
{
	while (headPtr)
	{
		Node *tempPtr = headPtr;
		headPtr = headPtr->nextPtr;
		free(tempPtr);
	}
}

void SortList(Node *headPtr)
{
	Node *curPtr = headPtr, *tailPtr = NULL;
	if (!curPtr->nextPtr) return;
	while (curPtr != tailPtr)
	{
		while (curPtr->nextPtr != tailPtr)
		{
			if (curPtr->val > curPtr->nextPtr->val)
			{
				int temp = curPtr->val;
				curPtr->val = curPtr->nextPtr->val;
				curPtr->nextPtr->val = temp;
			}
			curPtr = curPtr->nextPtr;
		}
		tailPtr = curPtr;
		curPtr = headPtr;
	}
}

bool IsSubSequence(Node *headPtrA, Node *headPtrB)
{
	while (headPtrA)
	{
		Node *headTempPtrA = headPtrA;
		Node *headTempPtrB = headPtrB;
		while (headTempPtrA && headTempPtrB && headTempPtrA->val == headTempPtrB->val)
		{
			headTempPtrA = headTempPtrA->nextPtr;
			headTempPtrB = headTempPtrB->nextPtr;
		}
		if (!headTempPtrB) return true;
		headPtrA = headPtrA->nextPtr;
	}
	return false;
}

Node *FindPosInList(Node *headPtr, int n)
{
	n--;
	if (n < 0) return NULL;
	while (n--) headPtr = headPtr->nextPtr;
	return headPtr;
}

void ExchangeRange(Node **headPtr, int r2, int l2, int r1, int l1)
{
	Node *leftA = FindPosInList(*headPtr, l1),
		 *leftPreA = FindPosInList(*headPtr, l1 - 1),
		 *rightA = FindPosInList(*headPtr, r1),
		 *leftB = FindPosInList(*headPtr, l2),
		 *leftPreB = FindPosInList(*headPtr, l2 - 1),
		 *rightB = FindPosInList(*headPtr, r2),
		 *tempPtr = rightB->nextPtr;
	if (leftA == *headPtr)
		*headPtr = leftB;
	else
		leftPreA->nextPtr = leftB;
	if (r1 + 1 == l2)
	{
		rightB->nextPtr = leftA;
		rightA->nextPtr = tempPtr;
		return;
	}
	rightB->nextPtr = rightA->nextPtr;
	leftPreB->nextPtr = leftA;
	rightA->nextPtr = tempPtr;
}
```

