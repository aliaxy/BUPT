/*
12-5 实验10_8_设计函数 void delcharfun(char *str,char ch)

设计函数 void delcharfun(char *str,char ch)实现从字符串str中删除指定的字符ch。
同一字母的大、小写按不同字符处理。

输入样例：
abcABCabc#
b
输出样例：
acABCac#
*/
#include <stdio.h>

void delcharfun(char *str, char ch)
{
    int i = 0, j;
    while (*(str + i) != '\0')
    {
        if (*(str + i) == ch)
            for (j = i; *(str + j) != '\0'; j++)
                *(str + j) = *(str + j + 1);
        else
            i++;
    }
}

int main(void)
{
    char ch, str[110];

    scanf("%s", str);
    getchar();
    scanf("%c", &ch);
    delcharfun(str, ch);
    printf("%s\n", str);
    return 0;
}