/*
11-6 实验8_7_蛇形矩阵

蛇形矩阵是一个n*n的矩阵，将整数1到n*n按照蛇形的顺序装入一个 n*n 的蛇形矩阵中，如样例所示分别为5阶和10阶蛇形矩阵。

输入格式:
只有一行，为一个整数n，代表蛇形矩阵的阶数，n的范围是1—100。

输出格式:
共n行，为蛇形矩阵。每行的每个元素用空格分隔，注意最后一个数的后面为换行符。

输入样例一:
5
输出样例一:
1 3 4 10 11
2 5 9 12 19
6 8 13 18 20
7 14 17 21 24
15 16 22 23 25
输入样例二:
10
输出样例二:
1 3 4 10 11 21 22 36 37 55
2 5 9 12 20 23 35 38 54 56
6 8 13 19 24 34 39 53 57 72
7 14 18 25 33 40 52 58 71 73
15 17 26 32 41 51 59 70 74 85
16 27 31 42 50 60 69 75 84 86
28 30 43 49 61 68 76 83 87 94
29 44 48 62 67 77 82 88 93 95
45 47 63 66 78 81 89 92 96 99
46 64 65 79 80 90 91 97 98 100
*/
#include <stdio.h>

#define MAX 100

void operate_1(int[][MAX], int);
void operate_2(int[][MAX], int);
void output(int[][MAX], int);

int main(void)
{
    int n,
        matrix[MAX][MAX];
    scanf("%d", &n);

    operate_1(matrix, n);
    operate_2(matrix, n);
    output(matrix, n);
    return 0;
}

void operate_1(int a[][MAX], int n)
{
    int i, j;
    a[0][0] = 1;
    for (i = 0; i < n; i++)
    {
        if (i)
        {
            if (i % 2)
                a[i][0] = a[i - 1][0] + 1;
            else
                a[i][0] = a[i - 1][0] + 2 * i;
        }
        for (j = 1; j < n - i; j++)
            if (i % 2)
                if (j % 2)
                    a[i][j] = a[i][j - 1] + 2 * i + 1;
                else
                    a[i][j] = a[i][j - 1] + 2 * j;
            else if (j % 2)
                a[i][j] = a[i][j - 1] + 2 * j;
            else
                a[i][j] = a[i][j - 1] + 2 * i + 1;
    }
}

void operate_2(int a[][MAX], int n)
{
    int i, j;
    a[n - 1][n - 1] = n * n;
    for (i = n - 1; i > 0; i--)
    {
        if (i - n + 1)
        {
            if ((n - i - 1) % 2)
                a[i][n - 1] = a[i + 1][n - 1] - 1;
            else
                a[i][n - 1] = a[i + 1][n - 1] - 2 * (n - i - 1);
        }
        for (j = n - 2; j >= n - i; j--)
            if ((n - i - 1) % 2)
                if ((n - j - 1) % 2)
                    a[i][j] = a[i][j + 1] - 2 * (n - i - 1) - 1;
                else
                    a[i][j] = a[i][j + 1] - 2 * (n - j - 1);
            else if ((n - j - 1) % 2)
                a[i][j] = a[i][j + 1] - 2 * (n - j - 1);
            else
                a[i][j] = a[i][j + 1] - 2 * (n - i - 1) - 1;
    }
}

void output(int a[][MAX], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
            printf("%d ", a[i][j]);
        printf("%d\n", a[i][j]);
    }
}