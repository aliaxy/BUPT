/*
14-4 实验10_11_字符串排序（指针数组)

1、设计函数char ** create1( int n ) ;，根据整数n创建一个长度为n的字符指针型动态一维数组，并返回动态数组第一个元素的地址。

2、设计函数char * create2( int n ) ;，根据整数n创建一个长度为n的字符型动态一维数组，并返回动态数组第一个元素的地址。

3、设计函数void sort( char** strArray , int size ) ; ，该函数可将字符指针数组strArray所指向的所有字符串按从小到大排列。

输入第一行为一个不超过200的整数n，代表待排序字符串的个数。然后输入n个字符串，每个字符串长度不会超过100。

输出为排序后的n个字符串，每个字符串占一行。

输入样例：
5
bbb
zzzzzz
aabbbccc
aaaaaa
abbbbb
输出样例：
aaaaaa
aabbbccc
abbbbb
bbb
zzzzzz
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101

char **create1(int n)
{
    char **p;
    p = (char **) malloc(sizeof(char *) * n);
    return (char **) p;
}
char *create2(int n)
{
    char *p;
    p = (char *) malloc(sizeof(char) * n);
    return (char *) p;
}
void sort(char **strArray, int size)
{
    int i, j;
    char *temp;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (strcmp(strArray[j], strArray[j + 1]) > 0)
            {
                temp = strArray[j];
                strArray[j] = strArray[j + 1];
                strArray[j + 1] = temp;
            }
        }
    }
}
int main(void)
{
    char **strArray;
    int n, i;

    scanf("%d", &n);
    strArray = create1(n);
    if (strArray != NULL)
    {
        for (i = 0; i < n; i++)
        {
            strArray[i] = create2(MAX);
            if (strArray[i] == NULL) return -1;
        }
    }
    else
        return -1;

    getchar();

    for (i = 0; i < n; i++)
        gets(strArray[i]);

    sort(strArray, n);

    for (i = 0; i < n; i++)
        printf("%s\n", strArray[i]);

    for (i = 0; i < n; i++)
        free(strArray[i]);
    free(strArray);

    return 0;
}