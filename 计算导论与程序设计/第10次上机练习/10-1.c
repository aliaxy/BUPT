/*
0-1 实验7_9_简单排序

设计函数 void bubbleSort(int a[],int n);，实现对整型数组的排序。

输入第一行为一个整数n(0<n<=1000),代表待排序元素的个数。第二行是n个整数，每个整数都不会超过int型的存储范围，为待排序元素。

输出只有一行，为输入的n个待排序元素按从小到大排序后的结果。（建议采用起泡排序算法）

建议设计一个辅助函数:
函数功能：依次输出数组中各个元素，数与数之间用空格分开，最后一个数后没有空格而是换行符
参数说明：数组名，数组内元素个数
void outputData(int data[],int elementCount) ;

注：此题大家可以练习各种排序算法。

输入样例：
8
49 38 65 97 76 13 27 4
输出样例：
4 13 27 38 49 65 76 97
*/
#include <stdio.h>

void bubbleSort(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
}
void outputData(int data[], int elementCount)
{
    int i;
    for (i = 0; i < elementCount - 1; i++)
        printf("%d ", data[i]);
    printf("%d\n", data[elementCount - 1]);
}

int main(void)
{
    int n, i, num[10010];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &num[i]);
    bubbleSort(num, n);
    outputData(num, n);
    return 0;
}