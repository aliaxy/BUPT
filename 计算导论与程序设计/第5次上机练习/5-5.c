/*
5-5 实验3_11_鸡兔同笼吗？

鸡有一个头两条腿，兔子有一个头4条腿，蜻蜓有一个头6条腿。没有例外。一个笼子里共有m个头，n条腿，问鸡、兔和蜻蜓各有多少？

输入格式:
只有一行，为两个正整数m和n，分别代表头的个数和腿的个数数。

输出格式:
有若干行，每一行为一组解，格式均为用空格分隔的三个整数，依次代表鸡的个数、解兔子的个数和蜻蜓的个数。多组解的输出顺序按解鸡的个数小到大排序。
测试数据保证可以用int存储。

输入样例:
15 40
输出样例:
在这里给出相应的输出。例如：

10 5 0
11 3 1
12 1 2
*/
#include <stdio.h>
#include <math.h>

int main(void)
{
    int heads, legs;
    scanf("%d %d", &heads, &legs);
    int rabbit = 0, dragonfly = 0;
    for (int i = 0; i <= heads; i++)
    {
        rabbit = (6 * heads - legs - 4 * i) / 2.0;
        dragonfly = (4 * i - 8 * heads + 2 * legs) / 4.0;
        if (rabbit >= 0 && dragonfly >= 0)
            printf("%d %d %d\n", i, rabbit, dragonfly);
    }

    return 0;
}