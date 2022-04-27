## 链表匹配

已知两个由正整数组成的无序序列A、B，每个序列的元素个数未知，但至少有一个元素。你的任务是判断序列B是否是序列A的连续子序列。假设B是“1 9 2 4 18”，A是“33 64 1 9 2 4 18 7”，B是A的连续子序列；假设B是“1 9 2 4 18”，A是“33 1 9 64 2 4 18 7”，B不是A的连续子序列。 要求： 建立两个单链表A、B用于存储两个正整数序列，然后按照题目的要求，判断链表B是否是链表A的连续子序列。正整数的输入用-1作为结束标志，注意-1不算这个正整数序列中的元素（不要统计-1）。在程序结束前要释放链表A、B中的所有节点。

#### Input

依次输入两个乱序的正整数序列A、B，序列中元素个数未知，但每个序列至少有一个元素，并以输入“-1”结束，每个序列占一行。

#### Output

如果序列B是序列A的连续子序列，则输出“ListB is the sub sequence of ListA.”，否则输出“ListB is not the sub sequence of ListA.”。 数据最多的测试用例节点数在100这个数量级，所有整数可以用int型存储。 **请注意输入输出格式。**

#### Sample Input

```
Sample 1:
5 4 3 2 1 -1
3 2 1 -1

Sample 2:
1 2 3 4 5 6 7 8 9 -1
1 2 3 4 5 6 7 8 0 -1
```

#### Sample Output

```
Sample 1:
ListB is the sub sequence of ListA.

Sample 2:
ListB is not the sub sequence of ListA.
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

int main(void)
{
    Node *headPtrA = CreateList(), *headPtrB = CreateList();

    if (IsSubSequence(headPtrA, headPtrB))
        printf("ListB is the sub sequence of ListA.");
    else
        printf("ListB is not the sub sequence of ListA.");

    FreeList(headPtrA), FreeList(headPtrB);
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
```
