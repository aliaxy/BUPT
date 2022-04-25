/*
10-4 实验7_11_循环移位

设计函数void shift(int *array , int num , int size ) ;，实现将整型数组内元素循环向左移若干位置。循环向左移位含义如下：

比如，原始数组a[0],a[1]...a[9]内元素依次为：1 2 3 4 5 6 7 8 9 10，
循环向左移1位后，则a[0],a[1]...a[9]内元素依次为：2 3 4 5 6 7 8 9 10 1，
循环向左移2位后，则a[0],a[1]...a[9]内元素依次为：3 4 5 6 7 8 9 10 1 2。依次类推。

输入样例：
10 1
1 2 3 4 5 6 7 8 9 10
输出样例：
2 3 4 5 6 7 8 9 10 1
*/
#include <stdio.h>

void shift(int *array, int num, int size)
{
    int temp, i, j;
    for (i = 0; i < num; i++)
    {
        temp = array[0];
        for (j = 0; j < size - 1; j++)
            array[j] = array[j + 1];
        array[j] = temp;
    }
}

int main(void)
{
    int i, n, p, array[100];

    scanf(" %d%d", &n, &p);
    for (i = 0; i < n; i++)
        scanf("%d", &array[i]);

    shift(array, p, n);
    for (i = 0; i < n - 1; i++)
        printf("%d ", array[i]);
    printf("%d\n", array[i]);

    return 0;
}