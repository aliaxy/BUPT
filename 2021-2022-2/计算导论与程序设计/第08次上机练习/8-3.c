/*
8-3 实验6_5_二进制的位数

设计递归函数int countBinary(int n); 用于将非负十进制整数n转换成二进制形式，并返回该二进制数的位数。
如十进制数13的二进制形式为1101，位数为4，那么调用countBinary(13)的结果为4。

输入与输出要求：
输入一个非负整数n。输出求得的结果，如输入“13”，输出“4”，占一行。

注意：此题要求递归求解，且不允许使用全局变量，其他方式不得分。

输入样例：
13
输出样例：
4
*/
#include <stdio.h>

int countBinary(int n)
{
    int num;
    if (n == 0 || n == 1)
        return 1;

    return countBinary(n / 2) + 1;
}

int main(void)
{
    int n;

    scanf("%d", &n);
    printf("%d\n", countBinary(n));

    return 0;
}