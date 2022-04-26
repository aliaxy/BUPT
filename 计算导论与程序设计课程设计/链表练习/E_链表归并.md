## 链表归并

已知有两个递增的正整数序列A和B，序列中元素个数未知，同一序列中不会有重复元素出现，有可能某个序列为空。现要求将序列B归并到序列A中，且归并后序列A的数据仍然按递增顺序排列。如果序列B中某些数据在序列A中也存在，则这些数据所在节点仍然留在序列B中，而不被归并到序列A中；否则这些数据所在节点将从序列B中删除，添加到序列A中。
要求：
建立两个单链表A、B用于存储两个正整数序列，然后按照题目的要求，将链表B中的元素归并到链表A中。在归并的过程中，不要释放B中的节点空间、然后建立新节点，而要改变指针的指向，使元素从B中删除并添加到A中。正整数序列按照递增顺序输入，用-1作为结束标志，注意-1不算这个正整数序列中的元素（不要统计-1）。在程序结束前要释放链表A、B中的所有节点。

#### Input

依次输入两个递增的正整数序列A和B，序列元素的个数未知，但以输入“-1”结束，每个正整数序列占一行。

#### Output

处理后的链表A中的元素，占一行；然后是处理后的链表B中的元素，占一行。每行的每个元素后有一个空格，注意最后一个元素后只有换行符，如果某个链表为空则，则输出“There is no item in X list.”
数据最多的测试用例节点数在100这个数量级，所有整数可以用int型存储。
**请注意输入输出格式。**

#### Sample Input

```
Sample 1:
1 3 4 5 6 7 -1
2 3 6 8 9 10 11-1

Sample 2:
-1
-1
```

#### Sample Output

```
Sample 1:
The new list A:1 2 3 4 5 6 7 8 9 10 11
The new list B:3 6

Sample 2:
There is no item in A list.
There is no item in B list.
```

####  Solution

````C
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int iData;
    struct node *pNext;
};
typedef struct node Node;

void CreateList(Node *stHeadA, Node *stHeadB);
void PrintList(Node *stHead);
void FreeList(Node *stHead);
void MergeSortList(Node *stHeadA, Node *stHeadB);

int main(void)
{
    Node stHeadA = {0, NULL}, stHeadB = {0, NULL};
    CreateList(&stHeadA, &stHeadB);


    MergeSortList(&stHeadA, &stHeadB);

    if (stHeadA.iData)
    {
        printf("The new list A:");
        PrintList(&stHeadA);
    }
    else
        printf("There is no item in A list.\n");
    if (stHeadB.iData)
    {
        printf("The new list B:");
        PrintList(&stHeadB);
    }
    else
        printf("There is no item in B list.\n");

    FreeList(&stHeadA);
    FreeList(&stHeadB);
    return 0;
}

void CreateList(Node *stHeadA, Node *stHeadB)
{
    int x;
    scanf("%d", &x);
    Node *pTail = stHeadA;
    while (~x)
    {
        Node *pTemp = (Node *) malloc(sizeof(Node));
        pTemp->iData = x, pTemp->pNext = NULL;

        pTail->pNext = pTemp;
        pTail = pTemp;
        stHeadA->iData++;
        scanf("%d", &x);
    }
    pTail = stHeadB;
    scanf("%d", &x);
    while (~x)
    {
        Node *pTemp = (Node *) malloc(sizeof(Node));
        pTemp->iData = x, pTemp->pNext = NULL;

        pTail->pNext = pTemp;
        pTail = pTemp;
        stHeadB->iData++;
        scanf("%d", &x);
    }
}

void PrintList(Node *stHead)
{
    if (!stHead) return;
    while (stHead->pNext)
    {
        printf("%d%c", stHead->pNext->iData, stHead->pNext->pNext ? ' ' : '\n');
        stHead = stHead->pNext;
    }
}

void FreeList(Node *stHead)
{
    if (!stHead->pNext || !stHead->iData) return;

    Node *pTemp = stHead->pNext;
    while (pTemp)
    {
        Node *pCurrent = pTemp;
        pTemp = pTemp->pNext;
        free(pCurrent);
    }
    stHead->pNext = NULL, stHead->iData = 0;
}

void MergeSortList(Node *stHeadA, Node *stHeadB)
{
    int f = 0;
    Node *pTempA = stHeadA->pNext, *pTempAPre = stHeadA, *pTempB = stHeadB->pNext, *pTempBPre = stHeadB;
    while (pTempA && pTempB)
    {
        if (pTempB->iData < pTempA->iData)
        {
            if (pTempAPre->iData == pTempB->iData)
            {
                pTempBPre = pTempB, pTempB = pTempB->pNext;
                f = 1;
                continue;
            }
            Node *pT = pTempB->pNext;
            pTempAPre->pNext = pTempB;
            pTempAPre = pTempB;
            pTempBPre->pNext = pTempB->pNext;
            pTempB->pNext = pTempA;
            pTempB = pT;
            stHeadA->iData++;
            stHeadA->iData--;
        }
        else
            pTempAPre = pTempA, pTempA = pTempA->pNext;
    }
    if (pTempB)
    {
        if (pTempB->iData == pTempAPre->iData) pTempBPre = pTempB, pTempB = pTempB->pNext, f = 1;
        pTempAPre->pNext = pTempB;
        pTempBPre->pNext = NULL;
        stHeadA->iData++;
    }
    stHeadB->iData = f;
}
````

