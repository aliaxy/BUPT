/*
2-4 实验2_3_表达式求值一

有表达式如下：
a / ( b * c - d )
请按要求计算。

输入格式:
只有一行，为4个用空格分隔的浮点数，依次代表a,b,c,d（请用double 类型存储）。

输出格式:
如果除数为0，则输出error，否则输出该表达式的值（保留1位小数）。

输入样例:
66.09 7.7 3.5 1.6
输出样例:
2.6
*/
#include <stdio.h>
#include <math.h>

int main(void)
{
    double a, b, c, d;
    double s;

    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    s = b * c - d;

    if (fabs(s) <= 1e-8)
        printf("error");
    else
    {
        s = a / s;
        printf("%.1lf", s);
    }

    return 0;
}