## 链表排序

已知一个正整数组成的无序序列，个数未知，但至少有一个元素，你的任务是建立一个单链表，并使用该链表存储这个正整数序列，然后将这个链表进行排序，使得排序后的链表为递增序列。正整数的输入用-1作为结束标志，注意-1不算这个正整数序列中的元素（不要统计-1）。在排序的过程中，你可以自己选择排序算法（冒泡排序、选择排序等），但必须是通过修改结点的指针域来进行排序，而不是对结点的数据域进行修改。程序结束后要释放所有节点占据的空间。

#### Input

一个元素个数未知的正整数序列，以输入“-1”结束，输入“-1”前至少输入一个正整数。

#### Output

经过排序后的链表，每个元素后有一个空格，注意最后一个元素后只有换行符。
数据最多的测试用例节点数在1000这个数量级，所有整数可以用int型存储。
**请注意输入输出格式。**

#### Sample Input

```
49 38 65 97 76 13 27 49 -1
```

#### Sample Output

```
The new list is:13 27 38 49 49 65 76 97
```

#### Solution

````c
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

int main(void)
{
	Node *headPtr = CreateList();

	SortList(headPtr);
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
````

