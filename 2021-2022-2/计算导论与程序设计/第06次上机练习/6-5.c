/*
6-5 实验4_4_进制转换一

已知一个只包含0和1的二进制数，二进制数的长度不大于10。你的任务是将其转换为十进制数并打印出来。

输入格式:
为一个只包含0和1的整数n（长度不超过10位），代表二进制数。

输出格式:
为转换得到的十进制数。

输入样例:
11111
输出样例:
31
*/
#include <stdio.h>

int main(void)
{
    int n, result = 0;
    scanf("%d", &n);

    int i = 1, t = n;

    while (t > 0)
    {
        i *= 10;
        t /= 10;
    }

    i /= 10;

    for (; i > 0; i /= 10)
    {
        int d;
        d = n / i;
        result = result * 2 + d;
        n %= i;
    }

    printf("%d", result);
    return 0;
}
