/*
10-3 实验7_12_插入排序

设计函数 void InsertSort(int a[],int n); 该函数使用插入排序算法，将数组a的前n个元素按照升序的方式排序。

输入与输出要求：
首先输入一个整数n（1<=n<=1000），代表待排序元素的个数。然后输入n个整数，每个整数不会超过int型的存储范围。

输出为n-1行，依次为1到n-1趟排序后数组内各个元素。每行输出的顺序为a[0]至a[n-1]，数与数之间用空格分开，注意第n个数后没有空格而是换行符。

输入样例：
8
49 38 65 97 76 13 27 49
输出样例：
38 49 65 97 76 13 27 49
38 49 65 97 76 13 27 49
38 49 65 97 76 13 27 49
38 49 65 76 97 13 27 49
13 38 49 65 76 97 27 49
13 27 38 49 65 76 97 49
13 27 38 49 49 65 76 97
*/
#include <stdio.h>

void InsertSort(int a[], int n)
{
    int i, j, flag;
    for (i = 1; i < n; i++)
    {
        flag = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > flag)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = flag;
        for (j = 0; j < n - 1; j++)
            printf("%d ", a[j]);
        printf("%d\n", a[j]);
    }
}

int main(void)
{
    int n, i, num[1000];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &num[i]);
    InsertSort(num, n);
    return 0;
}