/*
8-4 实验6_6_数列求值

现有序列： s = 1 + a + a^2+…+ a^{n+1}

其中a>0,n>0，且均为整数。 测试用例保证所有整数可以用int存储。
请写出递归求s的函数。

注意：此题要求递归求解，且不允许使用全局变量，其他方式不得分。

输入样例：
1 2
输出样例：
7
*/
#include <stdio.h>

int evaluation(int n, int a)
{
    int sum;
    if (n == -1)
        return 1;

    sum = 1 + evaluation(n - 1, a) * a;

    return sum;
}

int main(void)
{
    int n, a;

    scanf("%d%d", &n, &a);
    printf("%d\n", evaluation(n, a));

    return 0;
}