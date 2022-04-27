/*
12-1 实验9_4_句子输出

请按要求输出字符串。

输入格式:
第一行为一个整数n(0<n<=10)，表示将要输入的字符串的个数。
后边n行，每行一个字符串（长度不超过30，且不包含空格），
第n+2行为n个用空格分隔的整数，这n个整数为0到n-1，代表输出字符串的顺序。
如果第一个数字为1，则代表第1（从0开始计数）个输入的字符串第1（从1开始计数）个输出。
第二数字为0，则代表则代表第0（从0开始计数）个输入的字符串第2（从1开始计数）个输出。
后边依此类推。

输出格式:
共n行，每行一个字符串，输出顺序为输入中最后一行指定的顺序。。

输入样例:
3
world
Hello
!
1 0 2
输出样例:
Hello
world
!
*/
#include <stdio.h>
#include <stdlib.h>

char **create(int);
void input(char **, int *, int);
void output(char **, int *, int);
void free_m(char **, int *, int);

int main(void)
{
    int n, i;
    char **str = NULL;
    int *num = NULL;
    scanf("%d", &n);

    str = create(n);
    num = (int *) malloc(sizeof(int) * n);

    input(str, num, n);
    output(str, num, n);
    free_m(str, num, n);

    return 0;
}

char **create(int n)
{
    int i;
    char **a = NULL;
    a = (char **) malloc(sizeof(char *) * n);
    for (i = 0; i < n; i++)
        a[i] = (char *) malloc(sizeof(char) * 30);
    return (char **) a;
}

void input(char **str, int *num, int n)
{
    int i;
    for (i = 0; i < n; i++)
        scanf("%s", *(str + i));
    for (i = 0; i < n; i++)
        scanf("%d", num + i);
}

void output(char **str, int *num, int n)
{
    int i;
    for (i = 0; i < n; i++)
        puts(*(str + *(num + i)));
}

void free_m(char **str, int *num, int n)
{
    int i;
    for (i = 0; i < n; i++)
        free(str[i]);
    free(str);
    free(num);
}