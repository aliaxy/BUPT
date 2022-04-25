/*
4-1 实验3_1_简单问题

任意给定n个整数，求这n个整数序列的和、最小值和最大值。

输入格式:
第一行为一个整数n（0<n<100)，代表要输入的整数个数；第二行为用空格分隔的n个整数。测试用例保证所有整数及求和结果等均可以用int存储。

输出格式:
只有一行，为三个空格分隔的，依次代表整数序列的和、最大值和最小值。

输入样例:
5
10 20 30 40 50
输出样例:
150 50 10
*/
#include <stdio.h>

int main(void)
{
    int a = 0, b1 = 0, b2 = 0, i = 1, sum = 0, max = 0, min = 0;
    scanf("%d", &a);
    scanf("%d", &b1);
    sum = b1;
    min = b1;
    max = b1;
    while (i < a)
    {
        scanf("%d", &b2);
        sum = b2 + sum;
        max = max > b2 ? max : b2;
        min = min < b2 ? min : b2;
        i++;
    }
    printf("%d %d %d\n", sum, max, min);
    return 0;
}
