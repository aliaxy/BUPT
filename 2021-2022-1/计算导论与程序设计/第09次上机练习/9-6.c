/*
9-6 实验7_8_最长平台

给定一个长度为n的整数数组，数组中连续的相等元素构成的子序列称为平台。试设计算法，求出数组中最长平台的长度。

输入格式:
共2行，第一行为一个整数n(0<n<=1000)，代表输入整数个数，第二行为n个用空格分隔的整数。测试用例保证所有整数可以用int存储。

输出格式:
只有一行，为一个整数，代表输入数组的最长平台长度。

输入样例:
15
1 1 2 2 4 5 7 7 7 7 7 7 3 3 9
输出样例:
6
*/
#include <stdio.h>

void read(int[], int);
int lineMax(int[], int);

int main(void)
{
    int arr[1000],
        n;
    scanf("%d", &n);
    read(arr, n);
    printf("%d\n", lineMax(arr, n));

    return 0;
}

void read(int a[], int n)
{
    int i = 0;
    for (; i < n; i++)
        scanf("%d", &a[i]);
}

int lineMax(int a[], int n)
{
    int i = 0, count = 1, max = 1;
    for (; i < n; i++)
    {
        if (i && a[i] == a[i - 1])
        {
            count++;
            max = max > count ? max : count;
        }
        else
            count = 1;
    }
    return max;
}