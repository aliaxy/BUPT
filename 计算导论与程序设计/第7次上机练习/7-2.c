/*
7-2 实验5_6_设计函数mypow

设计函数int mypow(int x,int n)，返回正整数x的n次幂，如mypow(2,10)值为1024。

输入与输出要求：
输入两个非负整数x、和n，x的n次幂不会超过int型范围。输出计算结果，占一行。

输入样例：
2 10
输出样例：
1024
*/
#include <stdio.h>

int mypow(int x, int n)
{
    int pow = 1;
    for (int i = 0; i < n; i++)
    {
        pow *= x;
    }
    return pow;
}

int main(void)
{
    int x, n;

    scanf("%d%d", &x, &n);
    printf("%d\n", mypow(x, n));

    return 0;
}