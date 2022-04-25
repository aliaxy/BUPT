/*
11-4 实验8_5_寻找鞍点

任意给定一个n*m的矩阵，矩阵的行数为n,列数为m。你的任务是寻找该矩阵的鞍点。
一个矩阵的鞍点即该位置上的元素在所在行上最大，在所在列上最小。
有的矩阵也可能没有鞍点。不难证明，如果一个矩阵有鞍点，那么这个鞍点一定是唯一的。
如果某个矩阵只有1行（1列），则默认该行上的所有元素满足列上最小（行上最大）的要求。

测试用例保证同行或同列内没有相等的值。

输入格式:
共n+1行，第一行为用空格分隔的两个整数n、m，代表矩阵的行数与列数，n、m的范围均是1—100。后边n行为n*m个整数，即此矩阵的元素。具体见样例。测试用例保证所有整数可以用int存储。

输出格式:
只有一行，如果找到该矩阵的鞍点则输出“The saddle point is (x,y)=v.”，x为该鞍点所在的行，y为该鞍点所在的列，v为该位置上元素的值；如果该矩阵没有鞍点，则输出“There is no saddle point in the matrix.”。

输入样例:
4 5
1 2 3 4 5
2 4 6 8 10
3 6 9 12 15
4 8 12 16 20
输出样例:
The saddle point is (0,4)=5.
*/
#include <stdio.h>

#define MAX 100

void input(int[][MAX], int, int);
int findRowMax(int[], int);
int findColMin(int[][MAX], int, int);

int main(void)
{
    int n, m,
        matrix[MAX][MAX],
        maxCol, minRow,
        row = 0, found = 0;
    scanf("%d %d", &n, &m);

    input(matrix, n, m);
    while (row < n)
    {
        maxCol = findRowMax(matrix[row], m);
        minRow = findColMin(matrix, n, maxCol);
        if (minRow == row)
        {
            printf("The saddle point is (%d,%d)=%d.\n", row, maxCol, matrix[row][maxCol]);
            found = 1;
        }
        row++;
    }
    if (!found)
        printf("There is no saddle point in the matrix.\n");

    return 0;
}

void input(int data[][MAX], int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &data[i][j]);
}

int findRowMax(int data[], int n)
{
    int i, maxloc = 0;

    for (i = 1; i <= n - 1; i++)
        if (data[i] > data[maxloc])
            maxloc = i;

    return maxloc;
}

int findColMin(int data[][MAX], int rows, int col)
{
    int row, minRow = 0;

    for (row = 1; row <= rows - 1; row++)
        if (data[row][col] < data[minRow][col])
            minRow = row;

    return minRow;
}