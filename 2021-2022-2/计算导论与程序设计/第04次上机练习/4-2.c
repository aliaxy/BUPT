/*
4-2 实验3_2_密码文

已知一个英文单词，该单词中只包含大写字母“A—Z”与小写字母“a—z”。你的任务是将英文单词翻译成密码文。
翻译规则是把所有字母用它后面的第三个字母替换，并假设字符a接在字符z后面，字符A接在字符Z后面。例如：zero将被翻译成chur。

输入格式:
只有一行，为一个长度不超过100，只包含英文大小写字母的字符串（以回车换行符‘\n’结尾）。

输出格式:
只有一行，为对应字符串的密码文。

输入样例:
AZazbf
输出样例:
DCdcei
*/
#include <stdio.h>

int main(void)
{
    char ch;
    scanf("%c", &ch);
    while (ch != '\n')
    {
        if (ch == 'x')
            ch = 'a';
        else if (ch == 'y')
            ch = 'b';
        else if (ch == 'z')
            ch = 'c';
        else if (ch == 'X')
            ch = 'A';
        else if (ch == 'Y')
            ch = 'B';
        else if (ch == 'Z')
            ch = 'C';
        else
            ch += 3;
        printf("%c", ch);
        scanf("%c", &ch);
    }
    printf("\n");

    return 0;
}