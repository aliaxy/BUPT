/*
6-4 实验4_3_回文数

回文是指正读和反读都一样的数或文本段。例如，12321、55555、45554、11611都是回文数。
输入一个长度不超过10位的整数n，判断它是否是回文数。

输入格式:
只有一个整数n，即待判断的数字。测试用例保证n可以用int存储。

输出格式:
当n为回文数时输出“Yes”，否则输出“No”。

输入样例:
12321
输出样例:
Yes
*/
#include <stdio.h>

int roll(int num)
{
    int n = 0;
    while (num != 0)
    {
        n = num % 10 + n * 10;
        num /= 10;
    }

    return n;
}
int main(void)
{
    int num;
    scanf("%d", &num);

    if (num == roll(num))
        printf("Yes");
    else
        printf("No");

    printf("\n");

    return 0;
}