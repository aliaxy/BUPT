## 拆分链表

已知有一个乱序的字符序列L，序列中的字符可能是英文字母、数字字符或其它字符，字符的个数未知，每个字符之间用空格分开。字符序列用“-1”作为输入结束标志，这里你要把-1当做一个字符串对待，并且不算作字符序列中的元素。如下即为一个合法的字符序列：“a c 3 b a d 6 , & j m 8 7 2 V -1”。你的任务是将这个字符序列拆分为三个独立的序列A、B和C，其中序列A存放序列L中的字母，序列B存放序列L中的数字，序列C存放序列L中的其他字符，然后，将序列A、B和C分别按照ASCII码的大小关系进行升序排序。最终序列L将变为空序列。
要求：
建立四个单链表，分别存储序列L、A、B、C中的元素。字符序列的输入用“-1”作为结束标志。建立链表L时，建议使用scanf(“%s”,s);来读取字符序列中的字符，即把单独的字符看做一个字符串读取。当L建立后，你要按照问题描述中所述，将L拆分为A、B、C三个链表，然后对每个链表都进行排序，这部分的操作都应该是对指针进行修改，而不是删除节点与建立新节点。在程序结束前要释放链表A、B、C中的所有节点。

#### Input

一个乱序的字符序列，序列元素的个数未知，以输入“-1”结束，输入“-1”前可能没有其它元素，每个字符序列占一行。

#### Output

链表A中的元素，占一行；然后是链表B中的元素，占一行。最后是链表C中的元素，占一行。每行的每个元素后有一个空格，注意最后一个元素后只有换行符，如果某个链表为空则，则输出“There is no item in X list.”
数据最多的测试用例节点数在100这个数量级。
**请注意输入输出格式。**

#### Sample Input

```
Sample 1:
a c 3 b a d 6 , & j m 8 7 2 V -1

Sample 2:
z m v 1 a K 2 m p 9 a 0 a d -1
```

#### Sample Output

```
Sample 1:
The list A is: V a a b c d j m
The list B is: 2 3 6 7 8
The list C is: & ,

Sample 2:
The list A is: K a a a d m m p v z
The list B is: 0 1 2 9
There is no item in C list.
```

#### Solution

```c
#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node *pNext;
};
typedef struct node Node;

void CreateList(Node *stHead);
void SpiltList(Node *stHead, Node *Letter, Node *Number, Node *Other);
void PrintList(Node *stHead);
void FreeList(Node *stHead);
void BubbleSort(Node *stHead);

int main(void)
{
    Node stHead, Letter, Number, Other;
    stHead.data = Letter.data = Number.data = Other.data = '\0',
    stHead.pNext = Letter.pNext = Number.pNext = Other.pNext = NULL;
    CreateList(&stHead);

    SpiltList(&stHead, &Letter, &Number, &Other);

    BubbleSort(&Letter);
    BubbleSort(&Number);
    BubbleSort(&Other);

    if (Letter.pNext)
    {
        printf("The list A is:");
        PrintList(&Letter);
    }
    else
        printf("There is no item in A list.\n");
    if (Number.pNext)
    {
        printf("The list B is:");
        PrintList(&Number);
    }
    else
        printf("There is no item in B list.\n");
    if (Other.pNext)
    {
        printf("The list C is:");
        PrintList(&Other);
    }
    else
        printf("There is no item in C list.\n");


    FreeList(&Letter);
    FreeList(&Number);
    FreeList(&Other);

    return 0;
}

void CreateList(Node *stHead)
{
    char s[500];
    gets(s);
    char *p = s;
    Node *edTail = stHead;
    while (!(*p == '-' && *(p + 1) == '1'))
    {
        if (*p == ' ')
        {
            p++;
            continue;
        }
        Node *pTemp = (Node *) malloc(sizeof(Node));
        pTemp->data = *p, pTemp->pNext = NULL;
        edTail->pNext = pTemp;
        edTail = pTemp;
        p++;
    }
}

void SpiltList(Node *stHead, Node *Letter, Node *Number, Node *Other)
{
    Node *pTemp = stHead->pNext, *LetterTail = Letter, *NumberTail = Number, *OtherTail = Other;
    while (pTemp)
    {
        Node *pT = pTemp->pNext;
        char c = pTemp->data;
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            LetterTail->pNext = pTemp;
            pTemp->pNext = NULL;
            LetterTail = pTemp;
        }
        else if (c >= '0' && c <= '9')
        {
            NumberTail->pNext = pTemp;
            pTemp->pNext = NULL;
            NumberTail = pTemp;
        }
        else
        {
            OtherTail->pNext = pTemp;
            pTemp->pNext = NULL;
            OtherTail = pTemp;
        }
        stHead = pT;
        pTemp = pT;
    }
}

void PrintList(Node *stHead)
{
    Node *pTemp = stHead->pNext;
    while (pTemp)
    {
        printf(" %c", pTemp->data);
        pTemp = pTemp->pNext;
    }
    putchar('\n');
}

void FreeList(Node *stHead)
{
    if (!stHead || !stHead->pNext) return;
    Node *pTemp = stHead->pNext;
    while (pTemp)
    {
        Node *pFree = pTemp;
        pTemp = pTemp->pNext;
        free(pFree);
    }
}

void BubbleSort(Node *stHead)
{
    if (!stHead || !stHead->pNext || !stHead->pNext->pNext) return;
    Node *pre, *p, *tail;
    tail = NULL;
    while (stHead->pNext != tail)
    {
        pre = stHead;
        p = stHead->pNext;
        while (p->pNext != tail)
        {
            if (p->data > p->pNext->data)
            {
                pre->pNext = p->pNext;
                p->pNext = pre->pNext->pNext;
                pre->pNext->pNext = p;
            }
            else
                p = p->pNext;
            pre = pre->pNext;
        }
        tail = p;
    }
}
```

