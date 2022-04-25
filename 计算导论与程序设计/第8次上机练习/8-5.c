/*
8-5 实验6_8_整数逆序输出

请写出将一个整数逆序输出的函数。

注意：此题要求递归求解且不允许使用数组，不允许使用全局变量。如果违反要求则没有分。

输入样例：
1234
输出样例：
4321
*/
#include <stdio.h>

void reverse(int n)
{
    printf("%d", n % 10);
    if ((n /= 10) != 0)
        reverse(n);
}

int main(void)
{
    int n;

    scanf("%d", &n);
    reverse(n);
    printf("\n");
    return 0;
}