/*
5-4 实验3_10_同构数

所谓“同构数”是指这样的数，它出现在它的平方数的右边，例如5的平方数是25, 25的平方数是625，所以5和25都是同构数。
你的任务是判断整数x是否是同构数。若是同构数，输出“Yes”，否则输出“No”。x的取值范围是(1<=x<=10000)
如果输入的x不在允许范围内，则输出错误提示信息“x out of range”。

输入格式:
只有一个整数。测试用例保证所有输入可以用int存储。

输出格式:
只有一行，为判断结果。

输入样例:
20000
输出样例:
20000 out of range
*/
#include <stdio.h>
#include <math.h>

int cnc(int a)
{
    int i = 0;
    while (a != 0)
    {
        a /= 10;
        i++;
    }
    return i;
}

int resu(int num)
{
    int temp = num * num;
    int sum = 0;
    for (int i = 0; i < cnc(num); i++)
    {
        sum += temp % 10 * (int) pow(10, i);
        temp /= 10;
    }
    return sum;
}

int main(void)
{
    int num;
    scanf("%d", &num);

    if (num < 1 || num > 10000)
        printf("%d out of range", num);
    else if (resu(num) == num)
        printf("Yes");
    else
        printf("No");

    return 0;
}