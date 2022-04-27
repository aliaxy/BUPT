/*
9-4 实验7_6_数组交换

设有整数数组A和B，它们长度均为n。A数组中的元素为任意整数，不超过int型数据范围。
B数组中元素的值互不相同，且取值介于0至n-1之间。
现要求按数组B的内容调整A中数据的次序，比如当B[0]=9时，则要求将A[0]的内容与A[9]互换。

输入格式:
首先输入一个整数n（0<n<=10），代表数组A、B元素的个数。然后输入n个整数代表数组A中的元素。
最后输入n个整数代表数组B中的元素，注意B中元素的要求。测试用例保证所有整数可以用int存储。

输出格式:
调整后A数组的内容，数与数之间用空格分开，注意第n个数后没有空格而是换行符。

输入样例:
10
5 10 3 9 4 12 8 7 11 2
1 3 6 9 2 7 0 8 5 4
*/
#include <stdio.h>

void read(int[], int);
void operate(int[], int[], int);
void printArr(int[], int);

int main(void)
{
    int arrA[10],
        arrB[10],
        n;
    scanf("%d", &n);
    read(arrA, n);
    read(arrB, n);

    operate(arrA, arrB, n);

    printArr(arrA, n);

    return 0;
}

void read(int a[], int n)
{
    int i = 0;
    for (; i < n; i++)
        scanf("%d", &a[i]);
}

void operate(int a[], int b[], int n)
{
    int i = 0, temp;
    for (; i < n; i++)
    {
        temp = a[i];
        a[i] = a[b[i]];
        a[b[i]] = temp;
    }
}

void printArr(int a[], int n)
{
    int i = 0;
    for (; i < n - 1; i++)
        printf("%d ", a[i]);
    printf("%d\n", a[n - 1]);
}