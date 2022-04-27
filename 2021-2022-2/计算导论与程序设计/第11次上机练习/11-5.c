/*
11-5 实验8_6_矩阵变换

任意给定一个n*n的矩阵，矩阵的行数与列数均为n。
你的任务是通过行变换，使得矩阵每行元素的平均值按递增顺序排列。
如果出现有的行平均值相同的情况，则按照原顺序输出。

输入格式:
共n+1行，第一行为一个整数n代表矩阵的行数（列数），n的范围是1—100。后边n行为n*n个整数，即此矩阵的元素。矩阵元素的绝对值不会超过1000000。

输出格式:
共n行，为经过行变换后的新矩阵。每行的每个元素用空格分隔，注意最后一个元素后为换行符。具体见样例。

输入样例:
3
5 5 5
3 3 3
1 1 1
输出样例:
1 1 1
3 3 3
5 5 5
*/
#include <stdio.h>

#define MAX 101

void input(int[][MAX], int);
void operate(int[][MAX], int);
void output(int[][MAX], int);

int main(void)
{
    int n,
        matrix[MAX][MAX] = {0};

    scanf("%d", &n);

    input(matrix, n);
    operate(matrix, n);
    output(matrix, n);

    return 0;
}

void input(int data[][MAX], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &data[i][j]);
}

void operate(int data[][MAX], int n)
{
    int i, j, k, flag[MAX];
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            data[i][n] += data[i][j];
    for (i = 1; i < n; i++)
    {
        for (k = 0; k <= n; k++)
            flag[k] = data[i][k];
        j = i - 1;
        while (j >= 0 && data[j][n] > flag[n])
        {
            for (k = 0; k <= n; k++)
                data[j + 1][k] = data[j][k];
            j--;
        }
        for (k = 0; k <= n; k++)
            data[j + 1][k] = flag[k];
    }
}

void output(int data[][MAX], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
            printf("%d ", data[i][j]);
        printf("%d\n", data[i][j]);
    }
}