## 初识链表

已知一个正整数序列，个数未知，但至少有一个元素，你的任务是建立一个单链表，并使用该链表存储这个正整数序列，然后统计这个序列中元素的最大值与最小值，计算序列全部元素之和。正整数的输入用-1作为结束标志，注意-1不算这个正整数序列中的元素（不要统计-1）。

#### Input

一个正整数序列，正整数序列元素的个数未知，但以输入“-1”结束，输入“-1”前至少输入一个正整数。序列中的元素范围在1—999999999之间。

#### Output

三个正整数，即最大值、最小值、所有元素之和。
数据最多的测试用例节点数在1000这个数量级，所有整数可以用int型存储。
**请注意输入输出格式。**

#### Sample Input

```
1 4 99 21 50 61 32 4 -1
```

#### Sample Output

```
The maximum,minmum and the total are:99 1 272
```

#### Solution

```c
#include <stdio.h>
#include <stdlib.h>

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
void PrintList(Node *headPtr, int *max, int *min, int *sum);
void FreeList(Node *headPtr);

int main(void)
{
	Node *headPtr = CreateList();
	int min = 0x3f3f3f3f, max = 1, sum = 0;
	PrintList(headPtr, &max, &min, &sum);
	printf("The maximum,minmum and the total are:%d %d %d\n", max, min, sum);
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

void PrintList(Node *headPtr, int *max, int *min, int *sum)
{
	while (headPtr)
	{
		if (headPtr->val > *max) *max = headPtr->val;
		if (headPtr->val < *min) *min = headPtr->val;
		*sum += headPtr->val;
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
```


