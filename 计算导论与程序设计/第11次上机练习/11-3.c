/*
11-3 实验8_4_矩阵操作

现有一个矩阵，请你写程序求出某个数周围数字的和。这里我们规定，矩阵的左上角坐标为（1，1），
它右边一行的数的坐标依次为（1，2）、（1，3）等等，它下边一列的数的坐标依次为（2，1）、（3，1）等等，其余坐标以此类推。

输入格式:
第一行为两个整数m,n(1<m,n<10)，分别代表矩阵的行和列数。
接下来是m行n列整数，最后一行是两个整数x,y，分别代表指定的坐标。

输出格式:
为一个整数，为指定坐标周围的数字的和。需要注意的是当指定坐标在矩阵中间时，它周围有8个数，
当它在矩阵边缘时它周围有5个数，当它在矩阵角上时它周围只有3个数。测试用例保证合法且所有整数可以用int存储。

输入样例:
5 6
1 2 3 4 5 6
7 8 9 10 11 12
13 14 15 16 17 18
19 20 21 22 23 24
25 26 27 28 29 30
2 2
输出样例:
64
*/
#include <stdio.h>

#define MAX 11

void input(int[][MAX], int, int);
int operate(int[][MAX], int, int, int, int);

int main(void)
{
    int matrix[MAX][MAX] = {0},
        m, n,
        x, y;

    scanf("%d %d", &m, &n);

    input(matrix, m, n);
    scanf("%d %d", &x, &y);
    printf("%d\n", operate(matrix, m, n, x, y));

    return 0;
}

void input(int a[][MAX], int m, int n)
{
    int i, j;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
}

int operate(int a[][MAX], int m, int n, int x, int y)
{
    int i, j, sum = 0;
    for (i = x - 1; i <= x + 1; i++)
        for (j = y - 1; j <= y + 1; j++)
            sum += a[i][j];
    sum -= a[x][y];

    return sum;
}