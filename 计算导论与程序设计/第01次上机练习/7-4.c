/*
7-4 实验1_4_求圆的周长与面积
已知圆的半径（浮点数），求该圆的周长和面积并输出。圆的半径、周长、面积均要用双精度浮点型(double
型)变量来存储。在程序中，你还要定义一个符号常量，常量名为PI，即π值：3.14159265。圆的周长公式为2*π*R，圆的面积公式为π*R*R，其中R为圆的半径。

输入格式:
为一个正的浮点数，代表圆的半径。测试用例保证输入合法。

输出格式:
只有一行。假如输入的半径为5.5，则输出为“The perimeter is 34.5575, the area
is 95.0332.”。

输入样例:
5.5
输出样例:
The perimeter is 34.5575, the area is 95.0332.
*/
#include <stdio.h>

const double PI = 3.14159265;

int main(void)
{
    double r;
    scanf("%lf", &r);

    printf("The perimeter is %.4f, the area is %.4f.", 2 * PI * r, PI * r * r);
    return 0;
}