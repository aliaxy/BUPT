/*
5-2 实验3_8_位数对调

已知一个正整数n（可以用int存储），你的任务是将n的最低位与最高位上的数字对调，次低位与次高位上的数字对调，以此类推，直到中间位。最后得到一个新整数并将新的数字输出。需要注意的是：如果当最低位数字与最高位数字对调后，数字的长度变短（也就是最低位为0），则不能对这个数进行位数对调处理。

输入格式:
只有一个正整数，即n。

输出格式:
当n可以进行数字对调时，例如n=123，你应输出“321”；当n不可以进数字对调时，例如n=980，你应输出“The number cannot be changed.”。

输入样例:
1365
输出样例:
5631
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

int main(void)
{
    int num;
    int num_0 = 0;
    scanf("%d", &num);

    if (num % 10 == 0)
        printf("The number cannot be changed.");
    else
    {
        while (num != 0)
        {
            num_0 += num % 10 * (int) pow(10, cnc(num) - 1);
            num /= 10;
        }
        printf("%d", num_0);
    }
    return 0;
}