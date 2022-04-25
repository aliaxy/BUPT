/*
9-2 实验7_4_向量的内积

请写程序计算并输出向量的内积。

输入格式:
共两行，第一行一个整数n，1<=n<=10，第二行2Xn个整数（以空格分隔），即两个长度为n的一维数组（向量）。

输出格式:
只有一个整数，为计算结果。测试用例保证所有整数（包括计算过程中的）可以用int存储。

输入样例:
3
1 2 3 4 5 6
输出样例:
32
*/
#include <stdio.h>

void read(int[], int);
int inner(int[], int[], int);

int main(void)
{
    int n,
        arr_1[10],
        arr_2[10];
    scanf("%d", &n);
    read(arr_1, n);
    read(arr_2, n);

    printf("%d\n", inner(arr_1, arr_2, n));
    return 0;
}

void read(int a[], int n)
{
    int i = 0;
    for (; i < n; i++)
        scanf("%d", &a[i]);
}

int inner(int a[], int b[], int n)
{
    if (n > 1)
        return a[n - 1] * b[n - 1] + inner(a, b, n - 1);
    return a[0] * b[0];
}