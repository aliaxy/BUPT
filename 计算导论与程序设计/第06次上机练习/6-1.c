/*
6-1 实验3_13_最大公约数和最小公倍数

已知两个正整数m和n，求其最大公约数和最小公倍数。

输入格式:
两个用空格分隔的正整数m和n。

输出格式:
只有一行，为两个用空格分隔的正整数，依次代表m和n的最大公约数和最小公倍数。测试用例保证m、n及其最小公倍数可以用int存储。

输入样例:
12 36
输出样例:
12 36
*/
#include <stdio.h>

int main(void)
{
    int num0, num1;

    scanf("%d %d", &num0, &num1);

    int max = num0 >= num1 ? num0 : num1;
    int min = num0 <= num1 ? num0 : num1;
    int temp = 1;
    while (temp != 0)
    {
        temp = max % min;
        max = min;
        min = temp;
    }

    printf("%d %d\n", max, num0 / max * num1);

    return 0;
}