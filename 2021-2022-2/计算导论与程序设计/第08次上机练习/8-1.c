/*
8-1 实验6_2_递归求值二

现有序列： s = a + a + 3 + a + 6 +…+ a + 3 X n
请写出递归求s的程序。

输入只有一行，为两个用空格分隔正整数，分别代表n(0<n) 和 a(1<a)
输出也只有一行，为此情况下s的值。（测试用例保证所有整数可以用 int存储）。
注意：此题要求递归求解，且不允许使用全局变量，其他方式不得分。

输入样例：
1 2
输出样例：
7
*/

#include <stdio.h>

int getSum(int n, int a)
{
    int sum = 0;
    if (n == 0)
        return a;
    sum = a + 3 * n + getSum(n - 1, a);

    return sum;
}

int main(void)
{
    int n, a;

    scanf("%d%d", &n, &a);
    printf("%d\n", getSum(n, a));

    return 0;
}