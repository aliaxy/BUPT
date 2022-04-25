/*
8-2 实验6_4_二进制转十进制

设计递归函数int convert(int n);用于将二进制数n转换为十进制数并返回。
递归函数设计思路与提示：
当n==0或n==1时，函数返回n，否则返回n%10+convert(n/10)*2 。

输入与输出要求：
输入一个整数n，代表二进制数，其长度不大于10。输出转换后的十进制数，占一行。

注意：此题要求递归求解，且不允许使用全局变量，其他方式不得分。

输入样例：
101010
输出样例：
42
*/
#include <stdio.h>

int convert(int n)
{
    int num;
    if (n == 0 || n == 1)
        return n;
    num = n % 10 + convert(n / 10) * 2;

    return num;
}

int main(void)
{
    int n;

    scanf("%d", &n);

    printf("%d\n", convert(n));
    return 0;
}