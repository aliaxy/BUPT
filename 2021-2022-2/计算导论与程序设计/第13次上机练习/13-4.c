/*
13-4 实验10_5_指针数组初步

已知一个总长度不超过10000的字符串，字符串中只包含大写字母“A—Z”、小写字母“a—z”和空格‘ ’。
空格用于分割单词，空格的个数不超过1000个。你的任务是将字符串中用空格分隔的单词打印出来。
你要按照如下要求完成任务：
1.利用指针数组指向每个单词的开始位置。
2.把字符串中单词结束后的空格改为“\0”,然后使用指针数组将每个单词打印出来。

测试用例保证至少有一个单词。

输入样例：
You are great
输出样例：
You
are
great
*/
#include <stdio.h>

int getString(char *source, char *strPtr[])
{
    int i = 0, j = 0, flag = 0, temp = 0;
    char *p = source;
    if (*p == ' ')
        flag = 1;

    for (i = 0; source[i]; i++)
    {
        switch (flag)
        {
            case 1: //! 空格
                source[i] = '\0';
                if (source[i + 1] != ' ' && source[i + 1] != '\0')
                {
                    flag = 0;
                    p = source;
                    p += i + 1;
                }
                break;
            case 0: //! 字母
                if (!source[i + 1])
                {
                    strPtr[j] = p;
                    j++;
                }
                if (source[i + 1] == ' ')
                {
                    source[i + 1] = '\0';
                    strPtr[j] = p;
                    j++;
                    source[i + 1] = ' ';
                    flag = 1;
                }
        }
    }

    return j;
}

int main()
{
    char str[100005];
    char *strPtr[1005] = {0};
    int i, num;

    gets(str);
    num = getString(str, strPtr);
    for (i = 0; i < num; i++)
        puts(strPtr[i]);

    return 0;
}