/*
7-1 实验5_5_设计函数reverseNum

设计函数int reverseNum(int n)，返回正整数n反转后的形式，如reverseNum(12345)的值为54321。

输入与输出要求：
输入一个正整数n，n的取值范围不会超过int类型变量，n不会有前导0，n的结尾也不会有0。输出该正整数的反转形式，输出如“The reverse form of number 12345 is 54321.”，占一行。

输入样例：
12345
输出样例：
The reverse form of number 12345 is 54321.
*/
#include <stdio.h>

int reverseNum(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum = sum * 10 + n % 10;
        n /= 10;
    }
    return sum;
}

int main(void)
{
    int num;

    scanf("%d", &num);
    printf("The reverse form of number %d is %d.\n", num, reverseNum(num));

    return 0;
}