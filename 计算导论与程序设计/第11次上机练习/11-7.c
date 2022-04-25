/*
11-7 实验8_3_设计函数

设计函数将二维数组M中每列的最小元素，依次放入一维数组x中，二维数组M的行数为n,列数为m。

输入第一行为两个整数n、m，代表二维数组M的行数与列数，n、m的范围均是1—100。
然后是n*m个整数，即二维数组M的元素。输出x数组中的元素，每个元素用空格分隔。

输入样例：
3 4
22 45 56 30
19 33 45 38
20 22 66 40
输出样例：
19 22 45 30
*/
#include <stdio.h>

#define MAX 100

void findMin(int M[][MAX], int x[], int n, int m)
{
    int i, j, min;
    for (i = 0; i < m; i++)
    {
        min = M[0][i];
        for (j = 1; j < n; j++)
        {
            if (M[j][i] < min)
                min = M[j][i];
        }
        x[i] = min;
    }
}

int main(void)
{
    int matrix[MAX][MAX];
    int x[MAX];
    int n, m, i, j;

    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    findMin(matrix, x, n, m);

    for (i = 0; i < m - 1; i++)
        printf("%d ", x[i]);
    printf("%d\n", x[i]);

    return 0;
}