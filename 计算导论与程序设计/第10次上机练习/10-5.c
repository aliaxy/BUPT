/*
0-5 实验7_13_选择排序

设计函数 void SelectSort(int a[],int n); 使用选择排序算法对数组a的前n个元素按照升序的方式排序。

选择排序算法描述如下：
从a[0]到a[n-1]这段元素中找最小元素a[min]，a[0]和a[min]交换；
接着，从a[1]到a[n -1]这段元素中找最小元素a[min]，a[1]和a[min]交换；
依次类推，直到从a[n－2]到a[n -1]这段元素中找最小元素a[min]，a[n－2]和a[min]交换。

输入：首先输入一个整数n(1<n<=1000)，代表待排序元素的个数。然后是n个整数，每个整数不会超过int型的存储范围

输出为n-1行，依次为1到n-1趟排序后数组内各个元素。每行输出的顺序为a[0]至a[n-1]，数与数之间用空格分开，注意第n个数后没有空格而是换行符。

输入样例：
49 38 65 97 76 13 27 4
输出样例：
4 38 65 97 76 13 27 49
4 13 65 97 76 38 27 49
4 13 27 97 76 38 65 49
4 13 27 38 76 97 65 49
4 13 27 38 49 97 65 76
4 13 27 38 49 65 97 76
4 13 27 38 49 65 76 97
*/
#include <stdio.h>

int findMin(int data[], int startLoc, int endLoc)
{
    int i,
        minLoc = startLoc;
    for (i = startLoc + 1; i <= endLoc; i++)
        if (data[minLoc] > data[i])
            minLoc = i;
    return minLoc;
}

void outputData(int data[], int elementCount)
{
    int i;
    for (i = 0; i < elementCount - 1; i++)
        printf("%d ", data[i]);
    printf("%d\n", data[i]);
}

void selectSort(int data[], int elementCount)
{
    int i, temp, minLoc;

    for (i = 0; i < elementCount - 1; i++)
    {
        minLoc = findMin(data, i, elementCount - 1);
        if (i != minLoc)
        {
            temp = data[i];
            data[i] = data[minLoc];
            data[minLoc] = temp;
        }
        outputData(data, elementCount);
    }
}

int main(void)
{
    int n, i, num[1010];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &num[i]);
    selectSort(num, n);
    return 0;
}