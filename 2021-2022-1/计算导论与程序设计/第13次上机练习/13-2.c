/*
13-2 实验9_6_单词字符统计

请设计一个函数，参数为一个单词（字符串），假设max是单词中出现次数最多的字母的出现次数，min是单词中出现次数最少的字母的出现次数，
如果max-min是一个质数，则返回则max-min，否则返回-1。

测试程序输入：
只有一行，是一个单词，其中只可能出现小写字母，并且长度小于100。

测试程序输出：
如果输入单词的max-min是一个质数，输出max-min的值，否则输出-1。

输入样例：
banana
输出样例：
2
*/
#include <stdio.h>
#include <math.h>

#define MAXLEN 110

int isPrime(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int getResult(char word[])
{
    char *p = word;
    int max = 0, min = 100,
        i = 0, j;
    char ch;
    int z[26] = {0},
        n;

    while (*(p + i))
    {
        ch = *(p + i);
        n = ch - 'a';
        if (!z[n])
        {
            z[n]++;
            for (j = 1; *(p + i + j); j++)
                if (*(p + i + j) == ch)
                    z[n]++;
        }

        i++;
    }
    for (i = 0; i < 26; i++)
        if (z[i])
        {
            max = max > z[i] ? max : z[i];
            min = min < z[i] ? min : z[i];
        }

    if (isPrime(max - min))
        return max - min;
    else
        return -1;
}

int main(void)
{
    char word[MAXLEN];

    scanf("%s", word);
    printf("%d\n", getResult(word));

    return 0;
}