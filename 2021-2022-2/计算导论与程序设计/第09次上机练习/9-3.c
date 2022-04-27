/*
9-3 实验7_5_发工资

每到月底，公司就要给员工发工资。每个员工的工资都是由（100，50，20，10，5，2，1) 7种面值的钞票组成的。
为了发工资的简便，公司会尽量给员工发较大面值的钞票，
例如某个员工的工资为1260，那么公司会给员工12张100元的、1张50元的、1张10的钞票。
你的任务是，告诉你某员工的工资，你来计算如何给员工发工资。

输入格式:
为一个正整数n（可以用int存储），代表某位员工的工资。

输出格式:
为给该员工发的钞票面值与数量。具体格式见样例。

输入样例:
2352
输出样例:
100:23
50:1
2:1
*/
#include <stdio.h>

void operate(int[], int[], int);
void print(int[], int[]);

int main(void)
{
    int value[] = {100, 50, 20, 10, 5, 2, 1},
        page[7] = {0},
        n;
    scanf("%d", &n);

    operate(value, page, n);
    print(value, page);

    return 0;
}

void operate(int a[], int b[], int n)
{
    int i = 0;
    for (; n; i++)
    {
        b[i] = n / a[i];
        n %= a[i];
    }
}
void print(int a[], int b[])
{
    int i = 0;
    for (; i < 7; i++)
        if (b[i])
            printf("%d:%d\n", a[i], b[i]);
}