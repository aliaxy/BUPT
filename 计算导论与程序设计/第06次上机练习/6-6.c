/*
6-6 实验4_5_求幂值

编写一个程序，用泰勒级数计算e^x的值

输入格式:
只有一个浮点数x，即指数x,且x满足x<=20。

输出格式:
只有一个浮点数，保留4位小数。

输入样例:
3.7
输出样例:
40.4473
*/
#include <stdio.h>
#include <math.h>

int main(void)
{
    double num;
    double n = 1.0, sum = 0, i = 1;

    scanf("%lf", &num);

    while (fabs(n) >= 1e-8)
    {
        sum += n;
        n = n * num / i;
        i++;
    }

    printf("%.4f\n", sum);

    return 0;
}