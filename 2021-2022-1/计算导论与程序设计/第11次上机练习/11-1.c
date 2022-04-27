/*
11-1 实验8_1_矩阵转置

任意给定一个n*m的矩阵，矩阵的行数为n,列数为m。你的任务是实现矩阵的转置，即行列互换。

输入格式:
第一行为两个整数n、m，代表矩阵的行数与列数，n、m的范围均是1—100。然后输入n*m个整数，即此矩阵的元素。。

输出格式:
经过矩阵转置得到的新矩阵，新矩阵占m行，n列。每行的每个元素用空格分隔，注意最后一个数的后面为换行符。

输入样例:
3 5
5 5 5 5 5
3 3 3 3 3
1 1 1 1 1
输出样例:
5 3 1
5 3 1
5 3 1
5 3 1
5 3 1
*/
#include <stdio.h>

#define MAX 100

void input(int[][MAX], int, int);
void transpose(int[][MAX], int[][MAX], int, int);
void output(int[][MAX], int, int);

int main(void)
{
    int matrix[MAX][MAX],
        ans[MAX][MAX];
    int m, n;
    scanf("%d %d", &m, &n);

    input(matrix, m, n);
    transpose(matrix, ans, m, n);
    output(ans, n, m);

    return 0;
}

void input(int a[][MAX], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
}

void transpose(int a[][MAX], int b[][MAX], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            b[j][i] = a[i][j];
}

void output(int a[][MAX], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n - 1; j++)
            printf("%d ", a[i][j]);
        printf("%d\n", a[i][j]);
    }
}