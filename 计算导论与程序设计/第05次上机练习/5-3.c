/*
5-3 实验3_9_符合要求的数字

已知一个整数n，打印1到n所有除以m后所得商正好是它的各个数字平方和的数。

输入格式:
为两个用空格分隔的整数，它们依次代表n、m（1<m,n<10000)。

输出格式:
按从小到大的顺序依次输出所有满足条件的整数，每个数占一行。测试用例保证有满足条件的数。

输入样例:
1000 11
输出样例:
131
241
324
550
624
803
900
910
*/
#include <stdio.h>

int num_sum(int m)
{
    int sum = 0;
    while (m != 0)
    {
        sum += (m % 10) * (m % 10);
        m /= 10;
    }

    return sum;
}

int main(void)
{
    int n, num;
    scanf("%d %d", &n, &num);

    for (int i = 1; i <= n; i++)
    {
        if (num_sum(i) == i / num)
            printf("%d\n", i);
    }

    return 0;
}