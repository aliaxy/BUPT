/*
3-5 实验2_7_统计字符

给定一行字符，分别统计出其中英文字母、空格、数字和其他字符的个数。

输入格式:
只有一行，为一个字符序列，字符序列长度小于100，以回车键结束。

输出格式:
只有一行，为4个用空格分隔的整数，依次代表输入字符序列中英文字符，空格，数字以及其他字符的数量。

输入样例:
Happy new year #100101 !
输出样例:
12 4 6 2
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int letter = 0, space = 0, num = 0, others = 0, ch;

    while ((ch = getchar()) != '\n')
    {
        if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
            letter++;
        else if (ch == ' ')
            space++;
        else if (ch >= '0' && ch <= '9')
            num++;
        else
            others++;
    }

    printf("%d %d %d %d\n", letter, space, num, others);

    system("pause");

    return 0;
}