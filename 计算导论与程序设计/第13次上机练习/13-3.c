/*
13-3 实验9_7_设计函数int getVowel(char str[],char vowel[]);

设计函数int getVowel(char str[],char vowel[])，
将只包含小写字母的字符串str中的元音字母“a”“e”“i”“o”“u”复制到字符数组vowel，并返回字符串vowel的长度。

输入样例：
abcdefghiijklmn
输出样例：
4 aeii
*/
#include <stdio.h>

int getVowel(char str[], char vowel[])
{
    char *p1 = str,
         *p2 = vowel;
    int j = 0;
    for (; *p1; p1++)
    {
        switch (*p1)
        {
            case 'a':
                *(p2 + (j++)) = 'a';
                break;
            case 'e':
                *(p2 + (j++)) = 'e';
                break;
            case 'i':
                *(p2 + (j++)) = 'i';
                break;
            case 'o':
                *(p2 + (j++)) = 'o';
                break;
            case 'u':
                *(p2 + (j++)) = 'u';
                break;
        }
    }
    *(p2 + j) = '\0';
    return j;
}

int main(void)
{
    char vowel[101], str[101];
    int len;

    scanf("%s", str);
    len = getVowel(str, vowel);
    if (len > 0)
        printf("%d %s\n", len, vowel);
    else
        printf("%d\n", len);

    return 0;
}