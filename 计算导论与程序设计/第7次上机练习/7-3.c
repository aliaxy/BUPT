/*
7-3 实验5_10_设计函数judgeTriangle

设计函数int judgeTriangle(int a,int b,int c)，判断a、b、c三边是否能构成三角形，
如果能，那么进一步判断是属于哪种三角形（等边、等腰、直角、不规则三角形）。这里的a、b、c没有顺序之分。
当a、b、c三边不能构成三角形时，返回-1；当a、b、c三边构成不规则三角形时，返回0；
当a、b、c三边构成直角三角形时，返回1；当a、b、c三边构成等腰三角形时，返回2；当a、b、c三边构成等边三角形时，返回3。

输入与输出要求：
输入三个正整数a、b、c，分别代表三角形的三边，输出判断结果。
当无法构成三角形时输出“It is not a triangle.”；
当构成不规则三角形时输出“It is a scalenous triangle.”；
当构成直角三角形时输出“It is a right-angled triangle.”；
当构成等腰三角形时输出“It is an isosceles triangle.”；
当构成等边三角形时输出“It is a equilateral triangle.”。


输入样例：
13 5 12
输出样例：
It is a right-angled triangle.
*/
#include <stdio.h>

int judgeTriangle(int a, int b, int c)
{
    int temp = 0;
    if (a + b > c && b + c > a && a + c > b)
    {
        if (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a)
            temp = 1;
        else if (a == b && b == c)
            temp = 3;
        else if (a == b || b == c || a == c)
            temp = 2;
    }
    else
        temp = -1;
    return temp;
}

int main(void)
{
    int a, b, c;

    scanf("%d%d%d", &a, &b, &c);

    switch (judgeTriangle(a, b, c))
    {
        case -1: printf("It is not a triangle.\n"); break;
        case 0: printf("It is a scalenous triangle.\n"); break;
        case 1: printf("It is a right-angled triangle.\n"); break;
        case 2: printf("It is an isosceles triangle.\n"); break;
        case 3: printf("It is a equilateral triangle.\n"); break;
    }

    return 0;
}