/*
12-6 实验10_2_动态内存分配函数_1

1、设计函数int * create(int n) ;，
根据整数n创建一个长度为n的整型动态一维数组，并返回动态数组第一个元素的地址。
2、设计函数 void cal(int * array, int size) ;
该函数可计算array 所指向的动态一维数组中存储的size个整数的和及平均值，同时寻找其中的最大值、最小值。

输入共两行，第一行为一个整数n(0<n<100)。第二行为n个用空格分隔的整数。
第一行在主函数中输入，第二行需在函数cal中输入，并存储在 array 所指向的动态一维数组中。

输出共5行，前四行依次为和、平均值（精确到小数点后两位）、最大值、最小值。最后一行按原样输出输入的那n个整数。
前四行需在函数cal中输出，最后一行由主函数输出。

测试数据保证所有整数可以用int型存储。出题者存储浮点数时用的是 float。

输入样例：
10
1 2 3 4 5 6 7 8 9 10
输出样例：
55
5.50
10
1
1 2 3 4 5 6 7 8 9 10
*/
#include <stdio.h>
#include <stdlib.h>

int *create(int n)
{
    int *array = malloc(sizeof(int) * n),
        i;
    for (i = 0; i < n; i++)
        scanf("%d", array + i);

    return (int *) array;
}

void cal(int *array, int size)
{
    int sum = 0,
        max = *array,
        min = *array,
        i;
    float average;
    for (i = 0; i < size; i++)
    {
        sum += *(array + i);
        max = max > *(array + i) ? max : *(array + i);
        min = min < *(array + i) ? min : *(array + i);
    }
    average = (float) sum / size;
    printf("%d\n%.2f\n%d\n%d\n", sum, average, max, min);
}

int main(void)
{
    int *array, n, i;

    scanf("%d", &n);

    array = create(n);
    if (array == NULL)
        return -1;

    cal(array, n);
    for (i = 0; i < n; i++)
    {
        printf("%d", *(array + i));
        if (i == n - 1)
            printf("\n");
        else
            printf(" ");
    }

    free(array);

    return 0;
}