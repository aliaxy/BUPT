/*
3-1 实验2_8_打印实心菱形

已知一个整数n，你要根据n打印出n阶的实心菱形。

输入格式:
只有一个整数n(0<n<40，代表要打印的菱形阶数)。测试用例保证合法。

输出格式:
n阶实心菱形(占2乘n-1行)。

输入样例:
5
输出样例:
    *
   ***
  *****
 *******
*********
 *******
  *****
   ***
    *
*/
#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i; j++)
            printf(" ");
        for (int k = 1; k <= 2 * i - 1; k++)
            printf("*");
        printf("\n");
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= i; j++)
            printf(" ");
        for (int k = 1; k <= 2 * (n - i) - 1; k++)
            printf("*");
        printf("\n");
    }

    return 0;
}