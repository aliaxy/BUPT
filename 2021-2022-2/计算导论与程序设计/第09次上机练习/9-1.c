/*
9-1 实验7_3_奇数偶数

已知一个长度为n的整数数组，在保证原顺序的前提下，将该数组中所有的偶数放到所有的奇数之前，存到一个新数组中，并将新数组输出。

输入格式:
共2行，第一行为一个整数n(0<n<=200)，代表输入整数个数，第二行为n个用空格分隔的整数，需保存在待处理数组中。测试用例保证所有整数可以用int存储。

输出格式:
只有一行，为新数组中的元素，数与数之间用一个空格分隔，第n个数后是换行符。

输入样例:
10
3 9 4 5 8 7 10 2 6 1
输出样例:
4 8 10 2 6 3 9 5 7 1
*/
#include <stdio.h>

int odd(int[], int[], int);
void even(int[], int[], int, int);
void printArr(int[], int);

int main(void)
{
    int arr[200],
        num[200],
        n,
        i;
    scanf("%d", &n);
    i = odd(arr, num, n);
    even(arr, num, i, n);
    printArr(num, n);

    return 0;
}

int odd(int a[], int b[], int n)
{
    int i = 0, j = 0;
    for (; i < n; i++)
    {
        scanf("%d", &a[i]);
        if (!(a[i] % 2))
        {
            b[j] = a[i];
            j++;
        }
    }
    return j;
}

void even(int a[], int b[], int j, int n)
{
    int i = 0;
    for (; i < n; i++)
    {
        if (a[i] % 2)
        {
            b[j] = a[i];
            j++;
        }
    }
}

void printArr(int a[], int n)
{
    int i = 0;
    for (; i < n - 1; i++)
        printf("%d ", a[i]);
    printf("%d\n", a[n - 1]);
}